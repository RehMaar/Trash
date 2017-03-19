import java.lang.reflect.InvocationTargetException;
import java.lang.IllegalAccessException;
import java.lang.IllegalArgumentException;
import java.lang.NoSuchMethodException;
import java.lang.reflect.*;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.DisplayName;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

import datastructures.FibonacciHeap;
import datastructures.FibonacciHeap.Node;

@DisplayName("Testing FibonacciHeap module.")
class TestFiconacciHeap {

    static void checkNodeProperties(Node<Integer> node, int degree, boolean marked, Node<Integer> parent) {
        assertEquals(degree, node.getDegree());
        assertEquals(marked, node.getMarked());
        assertEquals(parent, node.getParent());
    }

    @Test
    @DisplayName("Testing helper functions.")
    void testHelper() {
        FibonacciHeap<Integer> t = new FibonacciHeap<Integer>();
        /* Getting access to private helper methods. */
        Method consolidate;
        Method cut;

        try {
            consolidate  = t.getClass().getDeclaredMethod("consolidate");
            cut          = t.getClass().getDeclaredMethod("cut", FibonacciHeap.Node.class, FibonacciHeap.Node.class);
        } catch (NoSuchMethodException e) {
            fail("Cannot access private method.");
            return;
        }
        consolidate.setAccessible(true);
        cut.setAccessible(true);
        /* Filling the heap. */
        FibonacciHeap.Node<Integer> node5 = t.insert(5);
        FibonacciHeap.Node<Integer> node1 = t.insert(1);
        FibonacciHeap.Node<Integer> node3 = t.insert(3);
        FibonacciHeap.Node<Integer> node4 = t.insert(4);
        FibonacciHeap.Node<Integer> node2 = t.insert(2);

        try {
            consolidate.invoke(t);
            /* Check minimum. */
            assertEquals(node1, t.minimum());

            /* Check node properties. */
            checkNodeProperties(node1, 2, false, null);
            checkNodeProperties(node2, 0, false, node1);
            checkNodeProperties(node3, 1, false, node1);
            checkNodeProperties(node4, 0, false, node3);
            checkNodeProperties(node5, 0, false, null);

        } catch(IllegalAccessException e) {
            fail("Cannot access private method: consolidate.");
            return;
        } catch(InvocationTargetException e) {
            fail("Cannot invoke private method: consolidate: " + e.getCause());
            return;
        }
        /* Cut out link between node and parent node, setting node as the root node.*/
        try {
            assertEquals(node2, node1.getChild());

            cut.invoke(t, node2, node1);

            assertEquals(1, node1.getDegree());
            assertEquals(node2, node1.next());

            cut.invoke(t, node4, node3);
        } catch(IllegalAccessException e) {
            fail("Cannot access private method: cut.");
            return;
        } catch(InvocationTargetException e) {
            fail("Cannot invoke private method: cut.");
            return;
        }
    }

    @Test
    @DisplayName("Testing HEAP_INSERT, EXTRACT_MIN on Integers.")
    void testInsert() {
        FibonacciHeap<Integer> t = new FibonacciHeap<Integer>();

        for(int i = 0; i < 10; i++) {
            t.insert(i);
            assertEquals(t.getSize(), i+1);
        }

        for(Integer i = 0; i < 10; i++) {
            assertEquals(i, t.minimum().getKey());
            assertEquals((10 - i), (int)t.getSize());
            assertEquals(i, t.extractMin().getKey());
        }
    }

    @Test
    @DisplayName("Testing MERGE")
    void testMerge() {
        FibonacciHeap<Integer> t = new FibonacciHeap<Integer>();
        FibonacciHeap<Integer> t1 = new FibonacciHeap<Integer>();

        FibonacciHeap.Node<Integer> tMin;
        FibonacciHeap.Node<Integer> t1Min;
        FibonacciHeap.Node<Integer> min;

        int tSize, t1Size;

        for(int i = 0; i < 10; i++) {
            t.insert(i);
        }

        for(int i = 10; i < 23; i++) {
            t1.insert(i);
        }

        tSize = t.getSize();
        t1Size = t1.getSize();

        tMin = t.minimum();
        t1Min = t1.minimum();

        min = tMin.compareTo(t1Min) > 0 ? t1Min : tMin;
        t.merge(t1);
        assertEquals(min, t.minimum());
        assertEquals(tSize+t1Size, t.getSize());
    }

    @Test
    @DisplayName("Testing DELETE")
    void testDelete() {
        FibonacciHeap<Integer> t = new FibonacciHeap<Integer>();
        FibonacciHeap.Node<Integer> node5 = t.insert(5);
        FibonacciHeap.Node<Integer> node1 = t.insert(1);
        FibonacciHeap.Node<Integer> node3 = t.insert(3);
        FibonacciHeap.Node<Integer> node4 = t.insert(4);
        FibonacciHeap.Node<Integer> node2 = t.insert(2);

        int size = t.getSize();
        assertEquals(node1, t.minimum());
    
        t.delete(node1);
        size--;

        assertEquals(node2, t.minimum());
        assertEquals(2, node2.getDegree());
        assertEquals(size, t.getSize());

        t.delete(node2);
        size--;
        
        assertEquals(size, t.getSize());
        assertEquals(node3, t.minimum());
        assertEquals(node4, t.minimum().next());

        t.delete(node3);
        size--;

        assertEquals(size, t.getSize());
        assertEquals(node4, t.minimum());
        assertEquals(node5, t.minimum().getChild());

        FibonacciHeap.Node<Integer> node0 = t.insert(0);
        size++;

        assertEquals(size, t.getSize());
        assertEquals(node0, t.minimum());
        assertEquals(node4, t.minimum().next());

        t.delete(node0);
        size--;

        t.delete(node4);
        size--;

        assertEquals(size, t.getSize());
        assertEquals(node5, t.minimum());
    }


    @Test
    @DisplayName("Testing DECREASE_KEY")
    void testDecreaseKey() {
        FibonacciHeap<Integer> t = new FibonacciHeap<Integer>();
        FibonacciHeap.Node<Integer> node5 = t.insert(5);
        FibonacciHeap.Node<Integer> node3 = t.insert(3);
        FibonacciHeap.Node<Integer> node4 = t.insert(4);
        FibonacciHeap.Node<Integer> node2 = t.insert(2);

        int size = t.getSize();

        t.decreaseKey(node5, 1);
        assertEquals(node5, t.minimum());
        assertEquals(size, t.getSize());

        t.decreaseKey(node4, 0);
        assertEquals(node4, t.minimum());
        assertEquals(size, t.getSize());

        t.decreaseKey(node3, 0);
        assertEquals(node4, t.minimum());
        assertEquals(size, t.getSize());

        boolean ex = false;
        try {
            t.decreaseKey(node3, 42);
        } catch(IllegalArgumentException e) {
            ex = true;
        }
        assertTrue(ex);
        assertEquals(size, t.getSize());
    }
}
