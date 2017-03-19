package datastructures;

import java.util.ArrayList;
import java.util.List;
import java.util.HashSet;
import java.lang.Comparable;
import java.lang.Number;
import java.lang.IllegalArgumentException;

public class FibonacciHeap {

    private Node min;
    private int size;

    /* MakeHeap */
    public FibonacciHeap() {
        this.min  = null;
        size = 0;
    }

    public FibonacciHeap(Integer key) {
        this.min  = new Node(key);
        size = 1;
    }

    public int getSize() {
        return this.size;
    }

    public Node minimum() {
        return this.min;
    }
 
    public Node insert(Integer key) {
        Node node = new Node(key);

        this.min = mergeLists(min, node);

        if (this.min != null)
            this.size++;
        return node;
    }

    public void merge(FibonacciHeap heap) {
        mergeLists(this.min, heap.minimum());
        this.size += heap.getSize();
    }

    public void delete(Node node) {
        this.decreaseKey(node, Integer.MIN_VALUE);
        this.extractMin();
    }

    public void decreaseKey(Node node, Integer key) {
        if (node.key.compareTo(key) < 0)
            throw new IllegalArgumentException("Key is larger then the current key at the node.");

        Node parent = node.parent;
        node.key = key;

        if (parent != null && node.compareTo(parent) < 0) {
            this.cut(node, parent);
            this.cascadingCut(parent);
        }
        if (null == this.min || node.compareTo(this.min) < 0) {
            this.min = node;
        }
    }

    public Node extractMin() {
        Node tmp = this.min;
        if (null != tmp) {
            if (null != tmp.child) {
                List<Node> ch = iterate(tmp.child);
                for (Node n : ch) {
                    this.min = mergeLists(this.min, n);
                    n.parent = null;
                }
            }

            Node node = tmp.next();
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

    private List<Node> iterate(Node root) {
        List<Node> l = new ArrayList();
        Node tmp;
        Node cur = root;
        do {
            tmp = cur.next();
            cur.left = cur.right = cur;
            l.add(cur);
            cur = tmp;
        } while(tmp != root);
        return l;
    }

    private void cascadingCut(Node y) {
        Node tmp = y.parent;

        if (null != tmp) {
            if (!tmp.marked) {
                tmp.marked = true;
            } else {
                this.cut(y, tmp);
                this.cascadingCut(tmp);
            }
        }
    }

    private void cut(Node child, Node parent) {
        if (parent.child == child) {
            parent.child = child.next() == child ? null : child.next();
        }
        removeFromRoots(child);
        parent.degree--;

        mergeLists(this.min, child);
        child.parent = null;
        child.marked = false;
    }

    private void removeFromRoots(Node node) {
        Node prev = node.right;
        Node next = node.left;

        prev.left = next;
        next.right = prev;

        node.left = node;
        node.right  = node;
    }

    private void removeFromChildren(Node node, Node parent) {
        if (parent.child == parent.child.right) {
            parent.child = null;
        } else if (parent.child == node) {
            parent.child = node.right;
            node.right.parent = parent;
        }

        node.left.right = node.right;
        node.right.left = node.left;
    }
    
    private void heapLink(Node y, Node x) {
        removeFromRoots(y);
        x.child = mergeLists(y, x.child);
        x.degree++;
        y.parent = x;
        y.marked = false;
    }


    private void printArrayNode(List<Node> ar) {
        for (int i = 0; i < ar.size(); i++) {
            Node n = ar.get(i);
            System.out.print("N: " + i + " Key: ");
            if (n != null)
                System.out.println(n.key);
            else
                System.out.println("null");
        }
    }
    private void consolidate() {
        int arrSize = (int)(Math.floor(Math.log(this.size)) / Math.log(2) + 2); //this.size + 1;
        List<Node> arrayNode = new ArrayList<Node>(arrSize);
        List<Node> it = iterate(this.min);
        /* Init arrayNode with zeros. */
        for (int i = 0; i < arrSize; i++) {
            arrayNode.add(null);
        }

        for (int i = 0; i < it.size(); i++) {
            Node x = it.get(i);
            int d = x.degree;
            while (null != arrayNode.get(d)) {
                Node y = arrayNode.get(d);
                if (x.compareTo(y) > 0) { /* Change */
                    Node temp = x;
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
                Node tmp = arrayNode.get(i);
                tmp.right = tmp.left = tmp;
                this.min = mergeLists(this.min,tmp);
                if (null == this.min || this.min.compareTo(tmp) > 0) {
                    this.min = tmp;
                }
            }
        }
    }

    private Node mergeLists(Node a, Node b) {

        if (a == null && b == null) {
            return null;
        }
        if (a == null) {
            return b;
        }
        if (b == null) {
            return a;
        }

        Node temp = a.right;
        a.right = b.right;
        a.right.left = a;
        b.right = temp;
        b.right.left = b;

        return a.compareTo(b) < 0 ? a : b;
    }

    public static class Node implements Comparable<Node> {
        private Node parent;
        private Node left;
        private Node right;
        private Node child;
        private int degree;
        private Integer key;
        private boolean marked;

        public Node(Integer key) {
            this.parent = null;
            this.child  = null;
            this.left   = this;
            this.right  = this;
            this.degree = 0;
            this.key    = key;
            this.marked = false;
        }

        public Node(Node node) {
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
        
        public Node getParent() {
            return this.parent;
        }

        public Integer getKey() {
            return this.key;
        }

        public Node getChild() {
            return this.child;
        }
        public Node next() {
            return this.left;
        }

        public int compareTo(Node node) {
            return this.key.compareTo(node.key);
        }

        public void print(int level) {
            Node curr = this;
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
                curr = curr.right;
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
        Node tmp = this.min;
        System.out.println("Roots: ");
        do {
            tmp.printNode();
            tmp = tmp.right;
        } while (tmp != this.min);
    }
}
