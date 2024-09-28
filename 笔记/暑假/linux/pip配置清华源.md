# 1、临时使用
`pip install -i https://pypi.tuna.tsinghua.edu.cn/simple some-package`
# 2、永久更改pip源
升级 pip 到最新的版本 (>=10.0.0) 后进行配置：
`pip install pip -U`

`pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple`

如果您到 pip 默认源的网络连接较差，临时使用镜像站来升级 pip：
`pip install -i https://pypi.tuna.tsinghua.edu.cn/simple pip -U`