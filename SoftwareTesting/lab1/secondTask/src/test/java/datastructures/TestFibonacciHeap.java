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

    static void checkNodeProperties(Node node, int degree, boolean marked, Node parent) {
        assertEquals(degree, node.getDegree());
        assertEquals(marked, node.getMarked());
        assertEquals(parent, node.getParent());
    }

    @Test
    @DisplayName("Testing helper functions.")
    void testHelper() {
        FibonacciHeap t = new FibonacciHeap();
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
        FibonacciHeap.Node node5 = t.insert(5);
        FibonacciHeap.Node node1 = t.insert(1);
        FibonacciHeap.Node node3 = t.insert(3);
        FibonacciHeap.Node node4 = t.insert(4);
        FibonacciHeap.Node node2 = t.insert(2);

        try {
            consolidate.invoke(t);
            /* Check minimum. */
            assertEquals(node1, t.minimum());
            /* Check node properties. */
            checkNodeProperties(node1, 2, false, null);
            checkNodeProperties(node2, 0, false, null);
            checkNodeProperties(node3, 1, false, node1);
            checkNodeProperties(node4, 0, false, node3);
            checkNodeProperties(node5, 0, false, node1);
        } catch(IllegalAccessException e) {
            fail("Cannot access private method: consolidate.");
            return;
        } catch(InvocationTargetException e) {
            fail("Cannot invoke private method: consolidate: " + e.getCause());
            return;
        }
        /* Cut out link between node and parent node, setting node as the root node.*/
        try {
            assertEquals(node4, node3.getChild());
            cut.invoke(t, node4, node3);
            assertEquals(0, node3.getDegree());
        } catch(IllegalAccessException e) {
            fail("Cannot access private method: cut.");
            return;
        } catch(InvocationTargetException e) {
            fail("Cannot invoke private method: cut.");
            return;
        }
    }

    @Test
    @DisplayName("Testing HEAP_INSERT on Integers.")
    void testInsert() {
        FibonacciHeap t = new FibonacciHeap();
		FibonacciHeap.Node node1;
		FibonacciHeap.Node node2;
		FibonacciHeap.Node node3;
		FibonacciHeap.Node node0;

		node1 = t.insert(1);
		assertEquals(node1, node1.next());
		assertEquals(node1, t.minimum());
		assertEquals(1, t.getSize());

		node2 = t.insert(2);
		assertEquals(2, t.getSize());
		assertEquals(node1, t.minimum());
		assertEquals(node2, node1.next());
		assertEquals(node1, node2.next());
		
		node3 = t.insert(3);
		assertEquals(3, t.getSize());
		assertEquals(node1, t.minimum());
		assertEquals(node2, node1.next());
		assertEquals(node3, node2.next());
		assertEquals(node1, node3.next());

		node0 = t.insert(0);
		assertEquals(4, t.getSize());
		assertEquals(node0, t.minimum());
		assertEquals(node1, node0.next());
		assertEquals(node2, node1.next());
		assertEquals(node3, node2.next());
		assertEquals(node0, node3.next());

    }

	@Test
	@DisplayName("Testing EXTRACT_MIN on Integers")
	void testExctractMin() {
        FibonacciHeap t = new FibonacciHeap();
        FibonacciHeap.Node min;
        
        for (int i = 0; i < 10; i++) {
			t.insert(i);
        }
		min = t.minimum();

        assertEquals(min, t.extractMin());
		min = t.minimum();
        assertEquals(1, (int)min.getKey());
        assertEquals(3, (int)min.getDegree());
        assertEquals(9, (int)min.next().getKey());
	}
    @Test
    @DisplayName("Testing MERGE")
    void testMerge() {
        FibonacciHeap t = new FibonacciHeap();
        FibonacciHeap t1 = new FibonacciHeap();

        FibonacciHeap.Node tMin;
        FibonacciHeap.Node t1Min;
        FibonacciHeap.Node min;

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
    @DisplayName("Testing DECREASE_KEY")
    void testDecreaseKey() {
        FibonacciHeap t = new FibonacciHeap();
        FibonacciHeap.Node node5 = t.insert(5);
        FibonacciHeap.Node node3 = t.insert(3);
        FibonacciHeap.Node node4 = t.insert(4);
        FibonacciHeap.Node node2 = t.insert(2);

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


    @Test
    @DisplayName("Testing DELETE")
    void testDelete() {
        FibonacciHeap t = new FibonacciHeap();
        FibonacciHeap.Node node5 = t.insert(5);
        FibonacciHeap.Node node1 = t.insert(1);
        FibonacciHeap.Node node3 = t.insert(3);
        FibonacciHeap.Node node4 = t.insert(4);
        FibonacciHeap.Node node2 = t.insert(2);

        int size = t.getSize();
        assertEquals(node1, t.minimum());
		t.print();    
        t.delete(node1);
        size--;

		t.print();    
        assertEquals(node2, t.minimum());
        assertEquals(2, node2.getDegree());
        assertEquals(size, t.getSize());

        t.delete(node2);
        size--;
        
		t.print();    
        assertEquals(size, t.getSize());
        assertEquals(node3, t.minimum());
        assertEquals(node4, t.minimum().next());

		t.print();    
        t.delete(node3);
        size--;

		t.print();    
        assertEquals(size, t.getSize());
        assertEquals(node4, t.minimum());
        assertEquals(node5, t.minimum().getChild());

        FibonacciHeap.Node node0 = t.insert(0);
        size++;

		t.print();    
        assertEquals(size, t.getSize());
        assertEquals(node0, t.minimum());
        assertEquals(node4, t.minimum().next());

        t.delete(node0);
        size--;

		t.print();    
        t.delete(node4);
        size--;

		t.print();    
        assertEquals(size, t.getSize());
        assertEquals(node5, t.minimum());
    }
}
