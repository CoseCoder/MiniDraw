# MiniDraw
## Figure父类
### Line，Ellipse，Rectangle，Polygon和Freehand子类（包括构造函数，Draw函数和SetEnd（设置终点）函数）
## FigureType枚举类型
### 表示当前绘制图形类型,包括kDefault 、kLine 、kEllipse、kRectangle、kPolygon、kFreehand
## ViewWidget类
### 继承自QWidget类，作为画板，重写鼠标点击，移动和释放响应函数和绘制消息响应函数，并实现设置当前绘制图形类型、完成多边形绘制（闭合多边形）、撤销上一步操作、恢复上一步操作、清空画板、设置画笔宽度和设置画笔颜色等函数
## MiniDraw类
### 继承自QMainWindow类，在类中设置交互界面，包括菜单栏，工具栏，状态栏，画板等，并设置各个菜单、工具被点击后相应的执行函数。
