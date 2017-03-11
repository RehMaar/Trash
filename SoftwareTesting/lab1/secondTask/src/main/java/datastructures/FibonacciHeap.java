package datastructures;

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
		Node<T> parent = node.parent;
		if (parent != null) {
			cut(node, parent);
			cascadingCut(parent);
		}
		this.min = node;
        this.extractMin();
    }

    public void decreaseKey(Node<T> node, T key) {
		if (key.compareTo(node.key) > 0)
    		throw new IllegalArgumentException("Key is larger then the current key at the node.");

		Node<T> parent = node.parent;
		node.key = key;

		if (parent != null && node.compareTo(parent) < 0) {
			this.cut(node, parent);
			this.cascadingCut(parent);
		}
		/* TODO: there is no condition this.min == null at the book. */
		if (null  == this.min|| node.compareTo(this.min) < 0) {
    		this.min = node;
		}
    }

    public Node<T> extractMin() {
        Node<T> tmp = this.min;

        if (null != tmp) {
            if (null != tmp.child) {
                Node<T> childTmp = tmp.child;
				do {
					childTmp.parent = null;
					mergeLists(this.min, childTmp);
					childTmp = childTmp.right;
                } while (tmp.child != childTmp);
            }
			removeFromRoots(tmp);
            if (tmp == tmp.right) {
                this.min = null;
            } else {
                this.min = tmp.right;
                this.consolidate();
            }
			this.size--;
        }
        return tmp;
    }

	private void cascadingCut(Node<T> y) {
		Node<T> tmp = y.parent;

		if (null != tmp) {
			y.marked = false;
		} else {
			this.cut(y, tmp);
			this.cascadingCut(tmp);
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
        Node<T> prev = node.left;
        Node<T> next = node.right;

        prev.right = next;
        next.left = prev;

        node.right = node;
        node.left  = node;
	}

	private void heapLink(Node<T> x, Node<T> y) {
    	removeFromRoots(y);
		/* Make y to be a child of x, x.degree++; */
		x.child = mergeLists(y, x.child);
		x.degree++;
		y.parent = x;
		y.marked = false;
	}

    private void consolidate() {
        int arrSize = this.size+ 1;
		Node<T>[] arrayNode = (Node<T>[]) new Object[arrSize];
		/* Init arrayNode with zeros. */
		for (int i = 0; i < arrSize; i++) {
			arrayNode[i] = null;
		}

		Node<T> tmp    = this.min;
		Node<T> tmpMin = this.min;

		do {
			Node<T> x = tmp;
			int d = x.degree;

			while (null != arrayNode[d]) {
				Node<T> y = arrayNode[d];
				if (x.compareTo(y) > 0) {
					Node<T> temp = x;
					x = y;
					y = temp;
				}
				this.heapLink(x, y);
				arrayNode[d] = null;
				d++;
			}
			arrayNode[d] = x;
			tmp = tmp.right;
		} while (tmp != tmpMin);

		this.min = null;
		for (int i = 0; i < arrSize; i++) {
			if (null != arrayNode[i]) {
				mergeLists(this.min, arrayNode[i]);
				if (null  == this.min|| this.min.compareTo(arrayNode[i]) > 0) {
					this.min = arrayNode[i];
				}
			}
		}
    }

    private Node<T> mergeLists(Node<T> min, Node<T> node) {

        if (null == min) {
            return node;
        }

        if (null == node) {
            return min;
        }
	
        Node<T> temp = min.left;
        min.left = node.left;
        min.left.right = min;
        node.left = temp;
        node.left.right = node;

        return min.compareTo(node) > 0 ? node : min;
    }

    public static class Node<T extends Comparable<T>>
    								implements Comparable<Node<T>> {
        public Node<T> parent;
        public Node<T> left;
        public Node<T> right;
        public Node<T> child;
        public int degree;
        public T key;
        public boolean marked;

        public Node(T key) {
            parent = null;
            child  = null;
            left   = this;
            right  = this;
            degree = 0;
            this.key    = key;
            marked = false;
        }

        public int compareTo(Node<T> node) {
			return this.key.compareTo(node.key);
        }

        public void print() {
			System.out.println("Key: " + this.key + " marked: " + String.valueOf(this.marked) +
 							   " degree: " + this.degree + " left_key: " + this.left.key + " right_key: " + this.right.key
			                  );
        }
    }

    public void print() {
		System.out.print("Size: " + this.size + " ");
		this.min.print();
    }
}
