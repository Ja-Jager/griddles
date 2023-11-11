# ESP-toaster

迁移到 ESP-IDF 平台，增加物联网功能。

死限期：2023 年 2 月 10 日

## 烘包机与炸炉相同功能

| 炸炉    | 烘包机     | 是否能通用 |
| ----- | ------- | ----- |
| 温度采集  | 温度采集    | ✔     |
| 继电器   | 继电器     | ✔     |
| 温度判断  | 温度判断    | ✔     |
| 超温保护  | 超温保护    | ✔     |
| 按键    | 按键      | ✔     |
| nvs   | nvs     | ✔     |
|       | 数码管     | ❌     |
| 旋转编码器 |         | ❌     |
| 倒计时   |         | ❌     |
|       | ToF 数面包 | ❌     |

## 完成事项

- [ ] 把当前 Toaster 代码迁移到 Fryer 里
  - [x] 温度采集
  - [x] 继电器
  - [x] 温度判断
  - [x] 超温保护
  - [ ] 按键
- [ ] Fryer 代码
  - [ ] 旋转编码器
  - [x] 倒计时
- [x] 电子板更改设计

## 注意

原本此项是有NTC_thermistor、esp_ntc组件的，但为了队列读取不重复，已经将其压缩放在C盘  
