idf_component_register(
    SRCS
        "roth.cpp"
        "Beacon/Beacon.cpp"
        "Battery/Battery.cpp"
        "TCPShell/TCPShell.cpp"

    INCLUDE_DIRS
        "."
        "Beacon"
        "Battery"
        "TCPShell"

)