package jp.ksgwr.kkkvs;

public class ValueIndex {

    static {
        System.loadLibrary("jkkkvs");
    }

    private long mHandle;

    public ValueIndex() {
        mHandle = init();
    }

    private native long init();

    public native int add(String data);

    //public native void put(int i, String data);

    //public native boolean exists(int i);

    public native String get(int i);

    public native void print();


}
