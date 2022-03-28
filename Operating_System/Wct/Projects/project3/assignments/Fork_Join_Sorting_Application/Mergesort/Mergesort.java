import java.util.Arrays;
import java.util.Scanner;
import java.util.concurrent.*;

public class Mergesort extends RecursiveAction {
	static final int THRESHOLD = 10;

	private int begin;
	private int end;
	private Integer[] array;

	public Mergesort(int begin, int end, Integer[] array) {
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
			int mid = begin + (end - begin) / 2;
            
			Mergesort leftTask = new Mergesort(begin, mid, array);
			Mergesort rightTask = new Mergesort(mid + 1, end, array);

			leftTask.fork();
			rightTask.fork();

			leftTask.join();
			rightTask.join();

			Integer[] temp = new Integer [end - begin + 1];
			
			int pos1 = begin, pos2 = mid + 1, k = 0;
			while (pos1 <= mid && pos2 <= end) {
				if (array[pos1].compareTo(array[pos2]) <= 0) temp[k ++] = array[pos1 ++];
				else temp[k ++] = array[pos2 ++];
			}
			while (pos1 <= mid) temp[k ++] = array[pos1 ++];
			while (pos2 <= end) temp[k ++] = array[pos2 ++];

			for (int i = 0; i < k; ++ i)
				array[i + begin] = temp[i];
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
		Mergesort task = new Mergesort(0, n - 1, array);

		pool.invoke(task);

		System.out.println(Arrays.toString(array));
	}
}