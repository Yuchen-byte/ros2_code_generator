# ROS2 Code Genertor

使用模版生成统一格式的 ROS2 代码方便多人协作，ROS 层与 Algorithm 层完全分离

### 使用方法

```bash
cd ros2_code_generator
python3 generate.py
```

### 说明

1. 默认添加：·`rclcpp` `std_msgs` `robot_msgs`
2. robot_msgs 的 scssignal 用于bag回看监控机器人算法运行
3. 特殊说明
`watch_dog_rate`是看门狗频率，使用定时器回调，看门狗用于监控
`visualization_rate`是可视化频率，用于Debug，主要用于`rviz`中的Debug
`watch_dog_timeout`是最大时间戳容忍时间，单位是秒,用于监控数据流异常话题
`loop_rate`是算法运行频率
`scs_signal` Safety Critical System​​ ，用于监控算法是否正常返回`True`,方便录包回放 Debug
4. `register.hpp`用于载入参数，相当于 declare + set parameter，主要用于终端显示，方便查看参数是否修改成功
### 输入


### TO DO 
目前只写了 rclcpp-executor，component 待完成