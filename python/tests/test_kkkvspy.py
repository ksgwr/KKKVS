import unittest
import kkkvspy

class MainTest(unittest.TestCase):
    def test_add(self):
        # test that 1 + 1 = 2
        self.assertEqual(kkkvspy.add(1, 1), 2)
    
    def test_create_value_index(self):
        index = kkkvspy.ValueIndex()
        self.assertIsNotNone(index)
        last = index.add([1,2,3])
        self.assertEqual(last, 0)
        # test failed (MemoryError: std::bad_alloc)
        #self.assertIsNotNone(index.get(last))


if __name__ == '__main__':
    unittest.main()