# Git

![ ](./pictures/3.jpg)

### git ��github�İ�
����˻�ȡ��Կ��
1. ��ȡ SSH keys
   * `cd ��/.ssh`   -- �鿴�Ƿ���ssh key 
   * `ssh-keygen -t rsa -C ��git�˺š�`  �������� һֱ **enter** ����
2. ��·������ `.ssh` ������洢��������ssh key����Կ��`id_rsa.pub`�ļ�����洢���ǹ�Կ �������Ҫ���ļ�
github�˰󶨣�
1. ��½github�˺� ���а�
![ ](./pictures/1.png)
![ ](./pictures/2.png)
����git��github�˺žͰ󶨺��� �Ϳ���ʹ��git�Ӳֿ�������/�ϴ�������
?��СС���ã���֮��Ĵ�������� ������ֺ�����Ͱ��������ǣ�
   * `git config --global user.name ��gitname�� `  �����û��� 
   * `git config --global user.email ��git���䡱 `  ��������


### git �������
* `sudo apt install git `     ��װgit
* `git clone git@github.com:zozo-919/workingData.git` ���ش����ַ

    ??�������Լ����ýű������� clone_x2100.sh 

* `git pull origin ��֧��`        ����Զ�̴���
* `git commit -m "�޸���Ϣ" `       �ύ�޸���־
* `git push origin ��֧��   `       ���ʹ�����Զ�̷�֧
* `git push -f origin ��֧�� `      ���Ͳ�����
* `git config core.fileMode false `     �鿴�����޸�
* `git branch -a `                  �鿴���з�֧
* `git diff filename(��commit id) `     �鿴�ļ�����
* `git status `                 �鿴�޸�����
* `git commit --amend   `       ��д��һ�ε��ύ
* `git remote -v `          �鿴git��������ַ
* `git reset --hard ��commit id��`      ���˵�ָ���޸�
* `git rebase -i commitid`      Ҫ�ϲ���commit
* `git config --global core.editor vim `    ��git�༭����Ϊvim
* `git reflog `       �鿴���ش�git�������ύ ����reset��ɾ����
* `git merge --squash `     �ϲ�������֧�Ĺ���
* `git show commit_id --stat `
* `git checkout -b ��֧��`    �������µķ�֧
* `find . -name "msa.h"  �����ļ�`

1. **������commit�ϲ���һ��**
   1. step1 ��git rebase -i commitid                -------commitid �ϲ��� �������µ�commitidҪ����id
   2. step2������༭����� ����һ��pack ���pack����Ϊs  Ȼ��`��wq` �����˳�(ע������git�༭����vim)
   3. step3��������� ��ͻ �����Ƚ����ͻ Ȼ�� git add ..... git rebase -- continue  ���������ϲ� ����git rebase --abort �ص����
   4. step4������ͻ��������� continue����� successfuly ����������ϲ��ɹ�

