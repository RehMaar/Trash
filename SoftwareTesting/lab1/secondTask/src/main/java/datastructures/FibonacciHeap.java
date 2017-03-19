package datastructures;

import java.util.ArrayList;
import java.util.List;
import java.util.HashSet;
import java.lang.Comparable;
import java.lang.IllegalArgumentException;

public class FibonacciHeap<T extends Comparable<T>> {

    private Node<T> min;
    private int size;

    /* MakeHeap */
    public FibonacciHeap() {
        this.min  = null;
        size = 0;
    }

    public FibonacciHeap(T key) {
        this.min  = new Node<T>(key);
        size = 1;
    }

    public int getSize() {
        return this.size;
    }

    public Node<T> minimum() {
        return this.min;
    }
 
    public Node<T> insert(T key) {
        Node<T> node = new Node<T>(key);

        this.min = mergeLists(min, node);

        if (this.min != null)
            this.size++;
        return node;
    }

    public void merge(FibonacciHeap<T> heap) {
        mergeLists(this.min, heap.minimum());
        this.size += heap.getSize();
    }

    public void delete(Node<T> node) {
        Node<T> parent = node.getParent();
        if (parent != null) {
            this.cut(node, parent);
            this.cascadingCut(parent);
        }
        this.min = node;
        this.extractMin();
    }

    public void decreaseKey(Node<T> node, T key) {
        if (node.key.compareTo(key) < 0)
            throw new IllegalArgumentException("Key is larger then the current key at the node.");

        Node<T> parent = node.parent;
        node.key = key;

        if (parent != null && node.compareTo(parent) < 0) {
            this.cut(node, parent);
            this.cascadingCut(parent);
        }
        if (null == this.min || node.compareTo(this.min) < 0) {
            this.min = node;
        }
    }

    public Node<T> extractMin() {
        Node<T> tmp = this.min;
        if (null != tmp) {
			if (null != tmp.child) {
    			List<Node<T>> ch = iterate(tmp.child);
    			for (Node<T> n : ch) {
					this.min = mergeLists(this.min, n);
					n.parent = null;
    			}
			}

			Node<T> node = tmp.next();
			removeFromRoots(tmp);
			if (tmp == node) {
    			this.min = null;
			} else {
				this.min = node;
				this.consolidate();
			}
			this.size--;
        }
        return tmp;
    }

	private List<Node<T>> iterate(Node<T> root) {
		List<Node<T>> l = new ArrayList();
		Node<T> tmp = root;
		do {
			l.add(tmp);
			tmp = tmp.next();
		} while(tmp != root);
		return l;
	}

    private void cascadingCut(Node<T> y) {
        Node<T> tmp = y.parent;

        if (null != tmp) {
            if (!tmp.marked) {
                tmp.marked = true;
            } else {
                this.cut(y, tmp);
                this.cascadingCut(tmp);
            }
        }
    }

    private void cut(Node<T> child, Node<T> parent) {
        removeFromRoots(child);
        parent.degree--;

        mergeLists(this.min, child);
        child.parent = null;
        child.marked = false;
    }

    private void removeFromRoots(Node<T> node) {
        Node<T> prev = node.right;
        Node<T> next = node.left;

        prev.left = next;
        next.right = prev;

        node.left = node;
        node.right  = node;
    }

    private void removeFromChildren(Node<T> node, Node<T> parent) {
        if (parent.child == parent.child.right) {
            parent.child = null;
        } else if (parent.child == node) {
            parent.child = node.right;
            node.right.parent = parent;
        }

        node.left.right = node.right;
        node.right.left = node.left;
    }
    
    private void heapLink(Node<T> y, Node<T> x) {
        removeFromRoots(y);
        x.child = mergeLists(y, x.child);
        x.degree++;
        y.parent = x;
        y.marked = false;
    }


	private void printArrayNode(List<Node<T>> ar) {
		for (int i = 0; i < ar.size(); i++) {
			Node<T> n = ar.get(i);
			System.out.print("N: " + i + " Key: ");
			if (n != null)
    			System.out.println(n.key);
			else
    			System.out.println("null");
		}
	}
    private void consolidate() {
        int arrSize = (int)(Math.floor(Math.log(this.size)) / Math.log(2) + 2); //this.size + 1;
        List<Node<T>> arrayNode = new ArrayList<Node<T>>(arrSize);
		List<Node<T>> it = iterate(this.min);
        /* Init arrayNode with zeros. */
        for (int i = 0; i < arrSize; i++) {
            arrayNode.add(null);
        }

        for (int i = 0; i < it.size(); i++) {
            Node<T> x = it.get(i);
            int d = x.degree;
            while (null != arrayNode.get(d)) {
                Node<T> y = arrayNode.get(d);
                if (x.compareTo(y) > 0) { /* Change */
                    Node<T> temp = x;
                    x = y;
                    y = temp;
                }
                this.heapLink(y, x);
                arrayNode.set(d, null);
                d++;
            }
            arrayNode.set(d, x);
        }
        this.min = null;
        for (int i = 0; i < arrSize; i++) {
            if (null != arrayNode.get(i)) {
                Node<T> tmp = arrayNode.get(i);
                tmp.right = tmp.left = tmp;
                this.min = mergeLists(this.min,tmp);
                if (null == this.min || this.min.compareTo(tmp) > 0) {
                    this.min = tmp;
                }
            }
        }
    }

    private Node<T> mergeLists(Node<T> a, Node<T> b) {

        if (a == null && b == null) {
            return null;
        }
        if (a == null) {
            return b;
        }
        if (b == null) {
            return a;
        }

        Node<T> temp = a.right;
        a.right = b.right;
        a.right.left = a;
        b.right = temp;
        b.right.left = b;

        return a.compareTo(b) < 0 ? a : b;
    }

    public static class Node<T extends Comparable<T>>
                                    implements Comparable<Node<T>> {
        private Node<T> parent;
        private Node<T> left;
        private Node<T> right;
        private Node<T> child;
        private int degree;
        private T key;
        private boolean marked;

        public Node(T key) {
            this.parent = null;
            this.child  = null;
            this.left   = this;
            this.right  = this;
            this.degree = 0;
            this.key    = key;
            this.marked = false;
        }

        public Node(Node<T> node) {
            this.parent = node.parent;
            this.child  = node.child;
            this.left   = node.left;
            this.right  = node.right;
            this.degree = node.degree;
            this.key    = node.key;
            this.marked = node.marked;
        }
        
        public boolean getMarked() {
            return this.marked;
        }
        
        public int getDegree() {
            return this.degree;
        }
        
        public Node<T> getParent() {
            return this.parent;
        }

        public T getKey() {
            return this.key;
        }

        public Node<T> getChild() {
            return this.child;
        }
        public Node<T> next() {
            return this.left;
        }
        public int compareTo(Node<T> node) {
            return this.key.compareTo(node.key);
        }
        public void print(int level) {
            Node<T> curr = this;
            do {
                StringBuilder sb = new StringBuilder();
                for (int i = 0; i < level; i++) {
                    sb.append(" ");
                }
                sb.append(curr.key.toString() + " " + curr.degree  +
                          " " + curr.marked);
                System.out.println(sb.toString());
                if (curr.child != null) {
                    curr.child.print(level + 1);
                }
                curr = curr.next();
            } while (curr != this);
        }

        public void printNode() {
            System.out.print("Key: " + this.key +
  //                             " node: " + this + 
  //                             " marked: " + String.valueOf(this.marked) +
                              " degree: " + this.degree +
                               " left_key: " + this.left.key +
                               " right_key: " + this.right.key
                              );
            if (null != this.child) {
                System.out.println(" child key: " + this.child.key);
            } else {
                System.out.print(" child: null\n");
            }
        }
    }

    public void print() {
        System.out.println("Fibonacci heap:");
        if (this.min != null) {
            this.min.print(0);
        }
    }
    public void printRoots() {
        Node<T> tmp = this.min;
        System.out.println("Roots: ");
        do {
            tmp.printNode();
            tmp = tmp.right;
        } while (tmp != this.min);
    }
}
