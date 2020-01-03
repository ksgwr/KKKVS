package jp.ksgwr.kkkvs;

import org.junit.Test;

import static org.assertj.core.api.Assertions.assertThat;

public class ValueIndexTest {

    @Test
    public void testCreateValueIndex() {
        ValueIndex index = new ValueIndex();
        assertThat(index).isNotNull();

        int i1 = index.getUncheckedRemovedIndex();

        assertThat(i1).isEqualTo(-1);

        // add 2 data
        String data1 = "data1";
        assertThat(index.add(data1)).isEqualTo(0);
        byte[] data2 = new byte[]{1,2,3};
        assertThat(index.add(data2)).isEqualTo(1);

        assertThat(index.exists(1)).isTrue();

        // get 2 data
        String actual1 = index.get(0);
        assertThat(actual1).isEqualTo(data1);
        byte[] actual2 = index.getAsBytes(1);
        assertThat(actual2).isEqualTo(data2);

        // remove soft 1 data
        index.remove(1);

        assertThat(index.exists(1)).isFalse();
        assertThat(index.getAsBytes(1)).isEqualTo(actual2);

        // add 1 data (new allocation)
        String data3 = "あ";
        assertThat(index.add(data3)).isEqualTo(2);

        assertThat(index.exists(2)).isTrue();
        assertThat(index.get(2).getBytes()).isEqualTo(data3.getBytes());

        // put 1 data (replace)
        byte[] data4 = "い".getBytes();
        index.put(2, data4);

        assertThat(index.getAsBytes(2)).isEqualTo(data4);

        // remove hard 1 data
        index.remove(0, true);

        assertThat(index.exists(0)).isFalse();
        assertThat(index.get(0)).isNull();

        // add 1 data (reuse)
        int i2 = index.getUncheckedRemovedIndex();

        assertThat(i2).isEqualTo(1);

        index.checkRemovedIndex(i2);

        int i3 = index.getUncheckedRemovedIndex();

        assertThat(i3).isEqualTo(-1);

        boolean findReuseIndex = false;
        for(int i=0;i<100;i++) {
            int tmpi = index.add("tmp");
            if(tmpi == 1) {
                findReuseIndex = true;
                break;
            }
        }
        assertThat(findReuseIndex).isTrue();
    }
}
