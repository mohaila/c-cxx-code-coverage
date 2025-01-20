#!/usr/bin/env python3

import app

if __name__ == '__main__':
    user = 'admin'
    password = 'Paswd123'
    resource = 'scada'
    connection_id = 0
    resource_id = 0

    app.app(user, password, resource, connection_id, resource_id)
