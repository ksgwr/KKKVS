package jp.ksgwr.kkkvs;

import org.junit.Test;

public class ValueIndexTest {

    @Test
    public void testHello() {
        new ValueIndex().print();
    }

    @Test
    public void testAdd() {
        ValueIndex index = new ValueIndex();
        System.out.println(index.add("abc"));
        System.out.println(index.add("あ"));
        System.out.println(index.get(0));
        System.out.println(index.get(1));
    }
}
