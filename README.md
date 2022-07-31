# WPA_oil_tank
风力摆飞行器——用于油罐除锈的弱化版本
PID_test：PID控制器
MRAC_test：模型参考自适应控制器
待办：带有前馈的PID控制器。
TO-DO:
- command_received变量用于控制飞行器的启动、停止等状态，这个功能还没加上，目前还是用'e'和's'控制启动停止的
- 目前还没加上从FOC读取旋翼转速并传回上位机的功能
- 目前还没有加入FOC死机、报错时自动停机的功能，这个功能比较重要，需要重点加入
- 记初始角度为0°，当飞行器的姿态角超出±90°（或者再进一步限制，比如60°？）时进行紧急停机，这个姿态限制的具体数值可以和老师讨论一下。为了防止参考姿态本身超出这个值的情况，可以对接收到的参考姿态值进行预处理，让它保持在±80°以内（加一点裕度用来超调）
