import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.DisplayName;
import static org.junit.jupiter.api.Assertions.assertEquals;

import datastructures.FibonacciHeap;
import datastructures.FibonacciHeap.Node;

@DisplayName("Testing FibonacciHeap module.")
class TestFiconacciHeap {

    @Test
    @DisplayName("Testing HEAP_INSERT, EXTRACT_MIN on Integers.")
    void testInsert() {
        FibonacciHeap<Integer> t = new FibonacciHeap<Integer>();

        for(int i = 0; i < 10; i++) {
            t.insert((i<<i)%10);
        }

        for(Integer i = 0; i < 10; i++) {
            assertEquals(t.minimum().key, i);
            assertEquals(t.extractMin().key, i);
        }
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

        /* { 3, 4, 2, min(1), 5 }*/
        t.delete(node1);
        assertEquals(t.minimum(), node2);
        assertEquals(t.minimum().right, node5);
        
        t.delete(node5);
        /* { 3, 4, min(2) }*/
        assertEquals(t.minimum().right, node3);

        t.delete(node4);
        /* { 3, min(2) }*/
        assertEquals(t.minimum().left, node3);

        t.delete(node3);
        /* { min(2) }*/
        assertEquals(t.minimum(), node2);
        assertEquals(t.minimum().left, node2);
        assertEquals(t.minimum().right, node2);

    }


	@Test
	@DisplayName("Testing DECREASE_KEY")
	void testDecreaseKey() {
        FibonacciHeap<Integer> t = new FibonacciHeap<Integer>();
        FibonacciHeap.Node<Integer> node5 = t.insert(5);
        FibonacciHeap.Node<Integer> node3 = t.insert(3);
        FibonacciHeap.Node<Integer> node4 = t.insert(4);
        FibonacciHeap.Node<Integer> node2 = t.insert(2);
        
		t.decreaseKey(node5, 1);
		assertEquals(t.minimum(), node5);

		t.decreaseKey(node4, 0);
		assertEquals(t.minimum(), node4);

		t.decreaseKey(node3, 0);
		assertEquals(t.minimum(), node4);
	}
}
