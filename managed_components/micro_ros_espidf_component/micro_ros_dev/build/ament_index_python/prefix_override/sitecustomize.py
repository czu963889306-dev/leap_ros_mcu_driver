import sys
if sys.prefix == '/root/.espressif/python_env/idf5.5_py3.13_env':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/root/maturo_project/leap_low_v1/managed_components/micro_ros_espidf_component/micro_ros_dev/install/ament_index_python'
