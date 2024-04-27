# QEMU for RISC-V 安装指南

本文档旨在帮助用户在Codespace环境中配置和安装QEMU for RISC-V。

## 步骤 1: 安装所需库

在Codespace的终端中，首先需要确保系统的软件包列表是最新的。

```bash
apt-get update
```

接着安装QEMU运行所需要的库。

```bash
apt-get install libpixman-1-0
apt-get install libglib2.0-0
```

## 步骤 2: 安装文本编辑器

为了编辑环境变量，我们需要一个文本编辑器，这里我们安装Vim。

```bash
apt install vim
```

## 步骤 3: 设置环境变量

接下来编辑`/etc/profile`文件，将QEMU和Nuclei的工具链添加到PATH环境变量中。

```bash
vim /etc/profile
```

在文件末尾添加以下行（替换`/path/to/your/application`为实际路径）：

```bash
export PATH="/path/to/your/application:$PATH"
```

保存并退出Vim（如果您熟悉Vim的话）：

```bash
:wq!
```

然后更新环境变量：

```bash
source /etc/profile
```

## 步骤 4: 下载并安装QEMU for RISC-V

下载QEMU for RISC-V。

```bash
wget https://www.nucleisys.com/upload/files/toochain/qemu/nuclei-qemu-2022.08-linux-x64.tar.gz
```

解压下载的文件。

```bash
tar -zxvf nuclei-qemu-2022.08-linux-x64.tar.gz
```

## 步骤 5: 编译并运行QEMU

首先进入到GCC编译目录。

```bash
cd /workspaces/ceshii/liteos_m/targets/riscv_nuclei_gd32vf103_soc_gcc/GCC
make all
cd build
```

运行QEMU。

```bash
/opt/qemu/bin/qemu-system-riscv32 -M gd32vf103v_rvstar -kernel Nuclei-rvstar-gd32vf103-soc.elf -serial stdio -nodefaults -nographic
```
