import unittest
import kkkvspy

class MainTest(unittest.TestCase):
    def test_add(self):
        # test that 1 + 1 = 2
        self.assertEqual(kkkvspy.add(1, 1), 2)

if __name__ == '__main__':
    unittest.main()