public class Sieve implements AutoCloseable {
    private long pointer;
	
	public Sieve(long size) throws IllegalArgumentException {
		if (size < 0)
			throw new IllegalArgumentException("Size out of range");
		pointer = CreateSieve(size);
	}
	
	@Override
	public void close() {
		DestroySieve(pointer);
	}
	
	public long size() {
		return GetSize(pointer);
	}
	
	public boolean isPrime(long at) throws IllegalArgumentException {
		if ((at < 0) || (at >= size()))
			throw new IllegalArgumentException("Size out of range");
		return GetIsPrime(pointer, at);
	}

    // Define native functions
    static {
        System.loadLibrary("wrapper");
    }	
	private static native long CreateSieve(long size);
	private static native void DestroySieve(long size);
	private static native long GetSize(long size);
	private static native boolean GetIsPrime(long size, long at);
}
