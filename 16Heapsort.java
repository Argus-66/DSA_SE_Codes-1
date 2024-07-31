// for printing the array in ascening order


import java.util.Arrays;

public class HeapSort {
    public static void heapSort(int[] arr) {
        int n = arr.length;

        // Build max heap
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        // Heap sort
        for (int i = n - 1; i > 0; i--) {
            // Swap root (maximum element) with last element
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            // Heapify root element
            heapify(arr, i, 0);
        }
    }

    // To heapify a subtree rooted at index i
    static void heapify(int[] arr, int n, int i) {
        int largest = i; // Initialize largest as root
        int left = 2 * i + 1; // Left child
        int right = 2 * i + 2; // Right child

        // If left child is smaller than root
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        // If right child is smaller than largest so far
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        // If largest is not root
        if (largest != i) {
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;

            // Recursively heapify the affected sub-tree
            heapify(arr, n, largest);
        }
    }

    // Main method to test the heap sort algorithm
    public static void main(String[] args) {
        int[] arr = {12, 11, 13, 15, 6, 7};
        System.out.println("Original array:");
        System.out.println(Arrays.toString(arr));
     
        heapSort(arr);

        System.out.println("Sorted array:");
        System.out.println(Arrays.toString(arr));
   
        // Minimum marks
        System.out.println("Minimum marks: " + arr[0]);
    }
}
