import unittest
import kkkvspy

class MainTest(unittest.TestCase):
    def test_add(self):
        # test that 1 + 1 = 2
        self.assertEqual(kkkvspy.add(1, 1), 2)
    
    def test_create_value_index(self):
        self.assertIsNotNone(kkkvspy.ValueIndex())

if __name__ == '__main__':
    unittest.main()