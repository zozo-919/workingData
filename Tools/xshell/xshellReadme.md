### 
#### xshell 用于远程登录
- 优化ssh登录速度：
	- #修改配置文件 先备份
		1. cp /etc/ssh/sshd_config /tmp/
		2. vi /etc/ssh/sshd_config	
   		 #直接输入 ：79 + 回车
				    79   GSSAPIAuthentication no
					115 UseDNS no   
					输入：wq 保存退出
	- #重启sshd服务
		1. systemctl restart sshd
	- #如果配置失败 还原配置 再重启sshd服务
