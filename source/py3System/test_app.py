import unittest
from unittest.mock import patch, Mock
import app
from py3System import result

class AppTest(unittest.TestCase):
    def setUp(self):
        self.user = 'admin'
        self.password = 'Paswd123'
        self.resource = 'scada'
        self.connection_id = 0
        self.resource_id = 0

        return super().setUp()

    def tearDown(self):
        return super().tearDown()

    @patch('py3System.resource_process')
    @patch('py3System.resource_unlock')
    @patch('py3System.resource_lock')
    @patch('py3System.resource_close')
    @patch('py3System.resource_open')
    @patch('py3System.system_disconnect')
    @patch('py3System.system_connect')
    def test_app_system_connect_error(self, 
                                      mock_connect: Mock, 
                                      mock_disconnect: Mock,
                                      mock_open: Mock,
                                      mock_close: Mock,
                                      mock_lock: Mock,
                                      mock_unlock: Mock,
                                      mock_process: Mock):
        mock_connect.return_value = -1
        status = app.app(user=self.user, password=self.password, resource=self.resource,
                         connection_id=self.connection_id, resource_id=self.resource_id)
        self.assertEqual(status, result.ko)
        mock_connect.assert_called_once_with(self.user, self.password)
        mock_disconnect.assert_not_called()
        mock_open.assert_not_called()
        mock_close.assert_not_called()
        mock_lock.assert_not_called()
        mock_unlock.assert_not_called()
        mock_process.assert_not_called()


    @patch('py3System.resource_process')
    @patch('py3System.resource_unlock')
    @patch('py3System.resource_lock')
    @patch('py3System.resource_close')
    @patch('py3System.resource_open')
    @patch('py3System.system_disconnect')
    @patch('py3System.system_connect')
    def test_app_system_open_error(self, 
                                      mock_connect: Mock, 
                                      mock_disconnect: Mock,
                                      mock_open: Mock,
                                      mock_close: Mock,
                                      mock_lock: Mock,
                                      mock_unlock: Mock,
                                      mock_process: Mock):
        mock_connect.return_value = 100
        mock_open.return_value = -1

        status = app.app(user=self.user, password=self.password, resource=self.resource,
                         connection_id=self.connection_id, resource_id=self.resource_id)
        self.assertEqual(status, result.ko)

        mock_connect.assert_called_once_with(self.user, self.password)
        mock_open.assert_called_once_with(100, self.resource)
        mock_disconnect.assert_called_once_with(100)

        mock_close.assert_not_called()
        mock_lock.assert_not_called()
        mock_unlock.assert_not_called()
        mock_process.assert_not_called()        

if __name__ == '__main__':
    unittest.main()