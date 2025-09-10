TEMPLATE = subdirs

# 子项目列表（按依赖顺序排列）
SUBDIRS += \
    myplugin \       # 基础模块（假设drawing是CanvasDRAW的实际模块名）
    App             # 依赖基础模块的应用


