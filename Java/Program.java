import java.util.Scanner;

public class Program {
    public static void main(String[] args) {
		Scanner input = new Scanner(System.in);
        System.out.print("Primes up to: ");
		long count = input.nextLong();

		long total = 0;

        // Call close() to 'delete' C++ pointer!!!
        try(Sieve sieve = new Sieve(count)) {
		    for (long i = 0; i < sieve.size(); ++i) {
		    	if (!sieve.isPrime(i)) continue;
		    	++total;
		    	System.out.print(i + " ");
		    }			
		}

		System.out.println();
		System.out.println(total + " primes in total");
    }
}
