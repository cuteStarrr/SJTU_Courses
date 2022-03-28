import java.util.Arrays;
import java.util.Scanner;
import java.util.concurrent.*;

public class Quicksort extends RecursiveAction {
	static final int THRESHOLD = 10;

	private int begin;
	private int end;
	private Integer[] array;

	public Quicksort(int begin, int end, Integer[] array) {
		this.begin = begin;
		this.end = end;
		this.array = array;
	}

	protected void compute() {
		if (end - begin + 1 <= THRESHOLD) {
			// Bubble Sort
			for (int i = end; i >= begin + 1; -- i)
				for (int j = begin; j < i; ++ j)
					if (array[j].compareTo(array[j + 1]) > 0) {
						Integer temp = array[j];
						array[j] = array[j + 1];
						array[j + 1] = temp;
					}
		} else {
			Integer pivot = array[begin];
			int low = begin, high = end;
			while (low < high) {
				while (low < high && array[high].compareTo(pivot) >= 0) -- high;
				if (low < high) array[low ++] = array[high];
				while (low < high && array[low].compareTo(pivot) <= 0) ++ low;
				if (low < high) array[high --] = array[low];
			}
			array[low] = pivot;
            
			Quicksort leftTask = new Quicksort(begin, low - 1, array);
			Quicksort rightTask = new Quicksort(low + 1, end, array);

			leftTask.fork();
			rightTask.fork();

			leftTask.join();
			rightTask.join();
		}
	}

	public static void main(String[] args) {
		ForkJoinPool pool = new ForkJoinPool();
		Scanner sc = new Scanner(System.in);

		int n = sc.nextInt();

		Integer[] array = new Integer[n];

		for (int i = 0; i < n; ++ i)
			array[i] = sc.nextInt();
		
		// use fork-join parallelism to sort the array
		Quicksort task = new Quicksort(0, n - 1, array);

		pool.invoke(task);

		System.out.println(Arrays.toString(array));
	}
}