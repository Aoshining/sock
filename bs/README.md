# 商品比价网站 Price Pulse

## 文件结构

```
.
├── BJ				# 项目代码
│   ├── frontend    			# 前端
│   ├── backend     			# 后端
│   ├── docker-compose.yml  	# Docker 部署配置文件
│   └── init.sql    			# 数据库初始化文件
├── docs            # 项目文档
├── 演示视频.mp4
└── README.md
```

## 项目启动

1. 获取项目文件

   解压项目文件压缩包或前往[我的仓库](https://github.com/Aoshining/sock.git)克隆`bs/`文件夹下项目文件
   
   ```sh
   git clone https://github.com/Aoshining/sock.git
   ```
   
1. 安装 Docker 并下载本项目所需镜像

   （如若出现连接超时无法下载，可更换网络或借助VPN后再次尝试）
   
   ```sh
   docker pull python:3.11-slim-buster
   docker pull node:16-slim
   docker pull nginx:stable-alpine
   docker pull mysql:8.0
   ```

3. 构建容器

   在**项目代码根目录下(`BJ/`)**执行如下命令：

   （如若出现连接超时无法下载，可为Docker导入镜像源、更换网络或借助VPN后再次尝试）：

   ```sh
   docker compose up --build
   ```

   > 等待数分钟后完成部署，如若后端报错无法连接至数据库，可能因为后端在数据库启动前启动，等待数据库启动成功后再次手动启动后端即可。

4. 访问服务

- 前端界面：http://localhost:80
- 后端服务器：http://localhost:8000

5. 操作指南

   见`doc/`中《用户使用手册》

6. 预备方案

   如若无法通过 Docker 部署启动项目，可直接访问云服务器上已部署好的网站：http://1.94.177.79:80 （服务器性能不太稳定，连接易超时）

## 服务配置

### 端口号

| 服务         | 端口号（本机） | 端口号（Docker） |
| ------------ | -------------- | ---------------- |
| 前端 Vue     | 80             | 80               |
| 后端 Django  | 8000           | 8000             |
| 数据库 MySQL | 3307           | 3306             |

### 数据库

- 数据库名：`compare`
- 端口号：`3307`
- 用户名：`root`
- 密码：`waz20040401`

可根据需求自行更改 `./BJ/docker-compose.yml` 与 `./BJ/backend/proj/settings.pysettings.py` 中的配置
