### 
#### xshell ����Զ�̵�¼
- �Ż�ssh��¼�ٶȣ�
	- #�޸������ļ� �ȱ���
		1. cp /etc/ssh/sshd_config /tmp/
		2. vi /etc/ssh/sshd_config	
   		 #ֱ������ ��79 + �س�
				    79   GSSAPIAuthentication no
					115 UseDNS no   
					���룺wq �����˳�
	- #����sshd����
		1. systemctl restart sshd
	- #�������ʧ�� ��ԭ���� ������sshd����
