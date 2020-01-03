package jp.ksgwr.kkkvs;

import java.nio.charset.StandardCharsets;

public class ValueIndex {

    static {
        System.loadLibrary("jkkkvs");
    }

    /**
     * reference: http://meryngii.hatenablog.com/entry/2014/04/10/221842
     */
    private long mHandle;

    public ValueIndex() {
        mHandle = init();
    }

    private native long init();

    public native int add(String data);

    private native int add2(byte[] data);

    public int add(byte[] data) {
        return add2(data);
    }

    public native void put(int i, String data);

    public void put(int i, byte[] data) {
        put(i, new String(data, StandardCharsets.UTF_8));
    }

    public native boolean exists(int i);

    public native String get(int i);

    public native byte[] getAsBytes(int i);

    public native void remove(int i, boolean hard);

    private native void remove2(int i);

    public void remove(int i) {
        remove2(i);
    }

    public native int getUncheckedRemovedIndex();

    public native void checkRemovedIndex(int i);

}
