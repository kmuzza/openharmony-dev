FROM ubuntu:18.04
WORKDIR /home/openharmony

# 使用华为云镜像加速
RUN sed -i "s@http://.*archive.ubuntu.com@http://repo.huaweicloud.com@g" /etc/apt/sources.list \
    && sed -i "s@http://.*security.ubuntu.com@http://repo.huaweicloud.com@g" /etc/apt/sources.list

# 安装基础依赖
RUN apt-get update -y && apt-get install -y apt-utils && \
    apt-get install -y binutils bison flex bc build-essential gcc g++ make && \
    apt-get install -y git zip unzip curl wget && \
    apt-get install -y python3.8 python3-pip && \
    apt-get install -y default-jre default-jdk && \
    apt-get install -y vim locales

# 设置环境变量
ENV LANG=en_US.UTF-8 \
    LANGUAGE=en_US.UTF-8 \
    LC_ALL=en_US.UTF-8 \
    PATH=/home/tools/llvm/bin:/home/tools/hc-gen:/home/tools/gcc_riscv32/bin:/home/tools/ninja:/home/tools/node-v14.15.4-linux-x64/bin:/home/tools/gn:$PATH

# 生成locales
RUN locale-gen "en_US.UTF-8"

# 替换python和sh的链接
RUN rm -rf /bin/sh /usr/bin/python /usr/bin/python3 /usr/bin/python3m && \
    ln -s /bin/bash /bin/sh && \
    ln -s /usr/bin/python3.8 /usr/bin/python3 && \
    ln -s /usr/bin/python3.8 /usr/bin/python3m && \
    ln -s /usr/bin/python3.8 /usr/bin/python

# 安装软件和工具
RUN apt-get install -y dosfstools mtools scons perl openssl libssl-dev cpio git-lfs m4 ccache zlib1g-dev tar rsync liblz4-tool genext2fs

# 清理apt缓存
RUN apt-get clean && rm -rf /var/lib/apt/lists/*

# 下载工具
# ...
# 在此处放置下载和安装工具的命令
# ...

# 安装npm全局包
RUN npm install -g @ohos/hpm-cli --registry https://mirrors.huaweicloud.com/repository/npm/

# 容器启动命令
CMD ["/bin/bash"]
