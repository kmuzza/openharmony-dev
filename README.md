# 1. 学习Qemu RISC-V的安装使用和OpenHarmony的编译与调试。

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

按键i进入编辑状态，光标移动到文档最后添加以下行

```bash
PATH=$PATH:/opt/gcc/bin/
```

按键esc 退出编辑状态，输入：wq保存编辑内容。

```bash
:wq!
```

更新环境变量：

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
cd /workspaces/Your_GithubName/liteos_m/targets/riscv_nuclei_gd32vf103_soc_gcc/GCC
make all
cd build
```

运行QEMU。

```bash
/opt/qemu/bin/qemu-system-riscv32 -M gd32vf103v_rvstar -kernel Nuclei-rvstar-gd32vf103-soc.elf -serial stdio -nodefaults -nographic
```
