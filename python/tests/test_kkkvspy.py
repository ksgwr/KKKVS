import unittest
import kkkvspy

class MainTest(unittest.TestCase):
    def test_add(self):
        # test that 1 + 1 = 2
        self.assertEqual(kkkvspy.add(1, 1), 2)
    
    def test_create_value_index(self):
        index = kkkvspy.ValueIndex()
        self.assertIsNotNone(index)

        i1 = index.getUncheckedOldestRemovedIndex()

        self.assertEqual(-1, i1)

        # add 2 data
        data1 = "data1"
        self.assertEqual(0, index.add(data1))
        data2 = bytes([1,2,3])
        self.assertEqual(1, index.add(data2))

        self.assertTrue(index.exists(1))

        # get 2 data
        actual1 = index.get(0)
        self.assertEqual(data1.encode('utf-8'), actual1)
        actual2 = index.get(1)
        self.assertEqual(data2, actual2)

        # remove 1 data
        index.remove(1)

        self.assertFalse(index.exists(1))

        # add 1 data (new allocation)
        data3 = b"data3"
        self.assertEqual(2, index.add(data3))

        self.assertTrue(index.exists(2))
        self.assertEqual(data3, index.get(2))

        # add 1 data (reuse)
        i2 = index.getUncheckedOldestRemovedIndex()

        self.assertEqual(1, i2)

        index.checkRemovedIndex(i2)

        i3 = index.getUncheckedOldestRemovedIndex()

        self.assertEqual(-1, i3)

        findReuseIndex = False
        for i in range(100):
            tmpi = index.add("tmp")
            if tmpi == 1:
                findReuseIndex = True
                break
        self.assertTrue(findReuseIndex)



if __name__ == '__main__':
    unittest.main()
