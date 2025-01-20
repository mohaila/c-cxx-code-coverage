import py3System
from py3System import result

def app(user: str, password: str, resource: str, connection_id: int, resource_id: int):
    status = py3System.system_connect(user, password)
    if status == -1:
        return result.ko
    else:
        connection_id = status

    status = py3System.resource_open(connection_id, resource)
    if status == -1:
        py3System.system_disconnect(connection_id)
        return result.ko
    else:
        resource_id = status

    status = py3System.resource_lock(connection_id, resource_id)
    if status != result.ok:
        py3System.resource_close(connection_id, resource_id)
        py3System.system_disconnect(connection_id)
        return result.ko

    status = py3System.resource_process(connection_id, resource_id)
    if status != result.ok:
        py3System.resource_unlock(connection_id, resource_id)
        py3System.resource_close(connection_id, resource_id)
        py3System.system_disconnect(connection_id)
        return result.ko

    status = py3System.resource_unlock(connection_id, resource_id)
    if status != result.ok:
        py3System.resource_close(connection_id, resource_id)
        py3System.system_disconnect(connection_id)
        return result.ko

    status = py3System.resource_close(connection_id, resource_id)
    if status != result.ok:
        py3System.system_disconnect(connection_id)
        return result.ko

    return py3System.system_disconnect(connection_id)                 
      