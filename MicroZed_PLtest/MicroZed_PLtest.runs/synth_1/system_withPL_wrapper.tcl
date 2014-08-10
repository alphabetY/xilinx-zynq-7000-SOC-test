# 
# Synthesis run script generated by Vivado
# 

  set_param gui.test TreeTableDev
set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000
create_project -in_memory -part xc7z010clg400-1
set_property target_language VHDL [current_project]
set_property board em.avnet.com:zynq:microzed:e [current_project]
set_param project.compositeFile.enableAutoGeneration 0
set_property ip_repo_paths E:/programming/project/Embedded/Vivado/MicroZed_PLtest/Adams_Peripheral_1.0 [current_fileset]

add_files E:/programming/project/Embedded/Vivado/MicroZed_PLtest/MicroZed_PLtest.srcs/sources_1/bd/system_withPL/system_withPL.bd
set_property used_in_implementation false [get_files -all e:/programming/project/Embedded/Vivado/MicroZed_PLtest/MicroZed_PLtest.srcs/sources_1/bd/system_withPL/ip/system_withPL_processing_system7_0_0/system_withPL_processing_system7_0_0.xdc]
set_property used_in_implementation false [get_files -all e:/programming/project/Embedded/Vivado/MicroZed_PLtest/MicroZed_PLtest.srcs/sources_1/bd/system_withPL/ip/system_withPL_rst_processing_system7_0_100M_0/system_withPL_rst_processing_system7_0_100M_0.xdc]
set_property used_in_implementation false [get_files -all e:/programming/project/Embedded/Vivado/MicroZed_PLtest/MicroZed_PLtest.srcs/sources_1/bd/system_withPL/ip/system_withPL_rst_processing_system7_0_100M_0/system_withPL_rst_processing_system7_0_100M_0_ooc.xdc]
set_property used_in_implementation false [get_files -all e:/programming/project/Embedded/Vivado/MicroZed_PLtest/MicroZed_PLtest.srcs/sources_1/bd/system_withPL/ip/system_withPL_rst_processing_system7_0_100M_0/system_withPL_rst_processing_system7_0_100M_0_board.xdc]
set_property used_in_implementation false [get_files -all e:/programming/project/Embedded/Vivado/MicroZed_PLtest/MicroZed_PLtest.srcs/sources_1/bd/system_withPL/ip/system_withPL_auto_pc_11/system_withPL_auto_pc_11_ooc.xdc]
set_property used_in_implementation false [get_files -all E:/programming/project/Embedded/Vivado/MicroZed_PLtest/MicroZed_PLtest.srcs/sources_1/bd/system_withPL/system_withPL_ooc.xdc]
set_msg_config -id {IP_Flow 19-2162} -severity warning -new_severity info
set_property is_locked true [get_files E:/programming/project/Embedded/Vivado/MicroZed_PLtest/MicroZed_PLtest.srcs/sources_1/bd/system_withPL/system_withPL.bd]

read_vhdl E:/programming/project/Embedded/Vivado/MicroZed_PLtest/MicroZed_PLtest.srcs/sources_1/bd/system_withPL/hdl/system_withPL_wrapper.vhd
read_xdc dont_touch.xdc
set_property used_in_implementation false [get_files dont_touch.xdc]
set_param synth.vivado.isSynthRun true
set_property webtalk.parent_dir E:/programming/project/Embedded/Vivado/MicroZed_PLtest/MicroZed_PLtest.data/wt [current_project]
set_property parent.project_dir E:/programming/project/Embedded/Vivado/MicroZed_PLtest [current_project]
synth_design -top system_withPL_wrapper -part xc7z010clg400-1
write_checkpoint system_withPL_wrapper.dcp
report_utilization -file system_withPL_wrapper_utilization_synth.rpt -pb system_withPL_wrapper_utilization_synth.pb