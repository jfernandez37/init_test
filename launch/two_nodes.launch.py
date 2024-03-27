import os
import xacro

from launch import LaunchDescription
from launch.actions import (
    IncludeLaunchDescription,
    OpaqueFunction,
)
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node

from ament_index_python.packages import get_package_share_directory

def launch_setup(context, *args, **kwargs):

    
    node_1 = Node(package="init_test",
        executable="node_1",
        name="node_1")
    
    node_2 = Node(package="init_test",
        executable="node_2",
        name="node_2")


    nodes_to_start = [
        node_1,
        node_2
    ]
    return nodes_to_start


def generate_launch_description():
    declared_arguments = []

    return LaunchDescription(declared_arguments + [OpaqueFunction(function=launch_setup)])