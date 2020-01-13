### 配置VPN的方法：

#### 1  下载并且购买发条云或者其他 VPN

#### 2 测试

        curl --socks5-hostname 127.0.0.1:1080 www.google.com.hk

        如果有结果，但是chrome上不了，说明vpn没问题，跳转到 3 来配置chrome

        如果没有结果，表示vpn配置的问题，此时跳转到 4 来重新配置shadowsocks

#### 3 chrome 配置 SwitchyOmega

      （1）下载 witchyOmega_Chromium.crx  https://github.com/FelisCatus/SwitchyOmega/releases

      （2）修改文件名称为 witchyOmega_Chromium.zip

      （3）解压缩为 witchyOmega_Chromium 的文件夹

      （4）将该文件夹拖拽到 chrome 的应用拓展之中

      （5）选择 proxy
                代理服务器   代理协议	代理服务器	代理端口
                （默认）    socks5    127.0.0.1  1080

        (6) 选择 应用选项

        (7) 使用以下命令行来测试

        curl --socks5-hostname 127.0.0.1:1080 https://www.youtube.com



#### 4  配置 shadowsocks

    参考以下链接进行配置：
https://mystery00.github.io/2018/08/23/Ubuntu%20Server%2018.04%20LTS%20%E4%BD%BF%E7%94%A8Shadowsocks-ShadowsocksR%E8%AE%BF%E9%97%AE%E4%BA%92%E8%81%94%E7%BD%91/