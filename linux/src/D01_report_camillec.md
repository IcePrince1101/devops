# Linux D01 отчет camillec

## Part 1. Установка ОС

- проверим версию Ubuntu с помощью `cat /etc/issue`.

![Part 1-1.](images/part1-1.jpg)

## Part 2. Создание пользователя

- Создадим нового пользователя командой `sudo useradd (name)`.

![Part 2.1](images/part2-1.jpg)

- Добавим нового пользователя `sudo usermod -a -G adm (name)`.

![Part 2.2](images/part2-2.jpg)

- Проверим, что пользователь появился при вызове `cat /etc/passwd`.

![Part 2.3](images/part2-3.jpg)

## Part 3. Настройка сети ОС

- Установим имя машины с помощью `hostnamectl set-hostname 'new-hostname'`.
- Кроме того, можно изменить `/etc/hostname` файл.

- Установим временную зону `sudo timedatectl set-timezone Europe/Moscow`.

![Part 3.2](images/part3-2.jpg)

- Имена сетевых интерфейсов можно получить, посмотрев в */sys/class/net* или командой `ip -br a show`.
- `lo` или 'loopback device' - это специальный виртуальный сетевой интерфейс, который компьютер использует для связи с самим собой. Он используется в основном для диагностики и устранения неполадок, а также для подключения к серверам, работающим на локальной машине.

![Part 3.3](images/part3-3.jpg)

- Для получения IP-адреса устройства, с которым я работаю, воспользуюсь командой `sudo dhclient -v enpOs3`, `enpOs3` я обнаружил выше.

- DHCP - Dynamic Host Configuration Protocol.

![Part 3.4](images/part3-4.jpg)

- Получу внешний IP-адрес с помощью `curl ifconfig.me`.
- также можно использовать `wget -qO- eth0.me`.

![Part 3.5](images/part3-5.jpg)

- Получим информацию о внутреннем IP-адресе `ip route | grep default`.

![Part 3.6](images/part3-6.jpg)

- Чтобы изменить сетевые настройки (ip, gw, dns), нужно изменить файл */etc/netplan/00-installer-config.yaml*. Удалить параметр `dhcp4`. Добавить адреса.

![Part 3.7](images/part3-7.jpg)

- Сохраним настройки при помощи `sudo netplan apply`. Перезагрузим систему с помощью `sudo reboot` и затем проверим потерю пакетов при пинговании удаленных хостов 1.1.1.1 и ya.ru. Необходимо, чтобы было 0% потери пакетов. Сделаем это с помощью `hostname -I && ping -c 4 1.1.1.1 | grep "stat\|loss" && ping -c 4 ya.ru`

![Part 3.8](images/part3-8.jpg)

## Part 4. Обновление ОС

- Выполняем команду `sudo apt update` update. Увидим список доступных пакетов.

![Part 4.1](images/part4-1.jpg)

- Обновляем системные пакеты до последней версии `sudo apt full-upgrade`.
- Еще раз вызываем `sudo apt update`.

![Part 4.2](images/part4-2.jpg)

## Part 5. Использование команды sudo.

- Sudo (superuser «do») позволяет системному администратору делегировать полномочия, чтобы дать определенным пользователям (или группам пользователей) возможность запускать некоторые (или все) команды от имени пользователя root или другого пользователя, обеспечивая контрольный журнал команд и их аргументов.

- Разрешим пользователю `Arioh` использовать sudo - `sudo usermod -a -G sudo Arioh`
- Меняем пароль у Arioh - `sudo passwd Arioh`
- Меняем пользователя `su - Arioh`
- Меняем hostname - `sudo hostnamectl set-hostname newhost`
- Выводим результат - `cat /etc/hostname`

![Part 5.1](images/part5-1.jpg)

## Part 6. Установка и настройка службы времени

- Выведем текущее время - `date`

![Part 6.1](images/part6-1.jpg)

-Устанавливаем NTP - `sudo apt install ntpdate`.

![Part 6.2](images/part6-2.jpg)

- Активируем NTP - `sudo timedatectl set-ntp on`
- Выведем текущую дату и время снова - `timedatectl show`.

![Part 6.3](images/part6-3.jpg)

## Part 7. Установка и использование текстовых редакторов

- Установим MCEDIT - `sudo apt install mcedit`

- Скриншот из VIM. Для выхода и сохранения нажимаем ESC и затем вводим :wq (w-write, q-quit).

![Part 7.1](images/part7-1.jpg)

- Скриншот из NANO. Для выхода нажимаем CTRL+X и подтверждаем сохранение, введя Y(от слова Yes).

![Part 7.2](images/part7-2.jpg)

- Скриншот из MCEDIT. Чтобы выйти с сохранением нажимаем F2, подтвеждаем ENTER, затем F10.

![Part 7.3](images/part7-3.jpg)

- Скриншот из VIM с исправленной строкой. Чтобы выйти без сохранения, нажимаем ESC, затем вводим :q!.

![Part 7.4](images/part7-4.jpg)

- Скриншот из NANO с исправленной строкой. Для выхода нажимаем CTRL+X и НЕ подтверждаем сохранение, введя N.

![Part 7.5](images/part7-5.jpg)

- Скриншот из MCEDIT с исправленной строкой. Чтобы выйти без сохранения, нажимаем F10 и затем n.

![Part 7.6](images/part7-6.jpg)

- Поиск в VIM - `/camillec`

![Part 7.7](images/part7-7.jpg)

- Замена в VIM - `:s/camillec/21 School 21`

![Part 7.8](images/part7-8.jpg)

- Для поиска в NANO надо нажать сочетание CTRL+W. 

![Part 7.9](images/part7-9.jpg)

- Для замены в NANO нажимаем комбинацию CTRL+\, пишем слово, которое надо заменить, жмем ENTER, пишем слово, на которое надо заменить, жмем ENTER, подтверждаем, нажав Y.

![Part 7.10](images/part7-10.jpg)

- для поиска в MCEDIT нажимаем F7, вводим нужное слово, жмем ENTER, оно выделится зеленым.

![Part 7.11](images/part7-11.jpg)

- Для замены в MCEDIT жмем F4, вводим слово, которое хотим заменить, на второй строке слово, на которое хотим заменить, жмем ENTER, подтверждаем замену.

![Part 7.12](images/part7-12.jpg)

## Part 8. Установка и базовая настройка сервиса SSHD

- Устанавливаем службу SSHd - `sudo apt install openssh-server`.
- Проверяем ее наличие - `ssh -V`

![Part 8.1](images/part8-1.jpg)

- Добавляем автостарт службы SSHd - `sudo update-rc.d ssh defaults`.

- Открываем файл конфигурации - `sudo vim /etc/ssh/sshd_config`. Меняем в нем порт - заменяем строку `Port 22` на `Port 2022`.

![Part 8.2](images/part8-2.jpg)

- Чтобы изменения вступили в силу - `/etc/init.d/ssh restart`

![Part 8.3](images/part8-3.jpg)

- Проверим наличие процесса - `ps -axfv | grep sshd`.
- -a - убирает лидеры сеанса и процессы,связанные с терминалом
- -x - отображает только те процессы, которыми владеем
- -f - полноформатный список
- -v - версия 

![Part 8.4](images/part8-4.jpg)

- Перезагрузим систему - `sudo reboot`. 
- Установим netstat - `sudo apt install net-tools`. 
- Вызываем `netstat -tan` и проверяем, что существует `tcp 0 0.0.0.0:2022 0.0.0.0:* LISTEN`.
- -t - показывает только tcp соединения
- -a - показывает состояние всех сокетов
- -n - показывает IP вместо сетевого имени

![Part 8.5](images/part8-5.jpg)

#####Столбцы:
- Proto - протокол, используемый системой
- Recv-Q - кол-во байт, не копированных пользовательской программой, подключенной к этому сокету
- Send-Q - кол-во байт, которые отправлены и находятся в очереди на отправку для данного сокета
- Local Address - локальный адрес и номер порта сокета
- Foreign Address - внешний адрес и номер порта сокета
- State - состояние сокета

- 0.0.0.0 в выводе означает, что SSH Daemon прослушивает все интерфейсы IPv4, которые есть у машины

## Part 9. Установка и использование утилит top, htop

- Установим top и htop.

- Вызовем - `top`

![Part 9.1](images/part9-1.jpg)

1. Uptime: 22 min;

2. Кол-во авторизованных пользователей: 1;

3. Общая загрузка системы: 0.0%;

4. Общее кол-во процессов: 121;

5. Загрузка сpu: 0.0 (user(us)(0.0) + system(sy)(0.0))

6. Загрузка памяти: 178.8 used, 392,2 cache.

7. PID процесса, занимающего больше всего памяти: 832

8. PID процесса, занимающего больше всего процессорного времени: 216

- для выхода - `q`

- Запускаем `htop`.
- Для сортировки используем F6.

- Сортированная по PID

![Part 9.2](images/part9-2.jpg)

- Сортировка по PERCENT_CPU

![Part 9.3](images/part9-3.jpg)

- Сортировка по PERCENT_MEM

![Part 9.4](images/part9-4.jpg)

- Сортировка по TIME

![Part 9.5](images/part9-5.jpg)

- Для работы с фильтром нажимаем F4
- фильтр по SSHd

![Part 9.6](images/part9-6.jpg)

- Для работы с поиском - F3
- Поиск syslog.

![Part 9.7](images/part9-7.jpg)

- Чтобы добавить вывод - нажмем F2. Настраиваем и подтверждаем - F10.

![Part 9.8](images/part9-8.jpg)

## Part 10. Использование утилиты fdisk

- Запустим `fdisk -l`.

![Part 10.1](images/part10-1.jpg)

- Название: /dev/sda;
- Размер: 50GiB;
- Кол-во секторов : 104857600;
- swap размер (`free -h`): 3.8Gi.

![Part 10.2](images/part10-2.jpg)

## Part 11. Использование утилиты df

- Запустим `df`

![Part 11.1](images/part11-1.jpg)

- Размер пространства: 24590672.
- Места использовано: 7323640.
- Места свободно: 15992564.
- Процент использования: 32.
- Единицы измерения: Килобайты.

![Part 11.2](images/part11-2.jpg)

- Размер пространства: 24G.
- Места использовано: 7G.
- Места свободно: 16G.
- Процент использования: 32.

- Тип файловой системы - ext4

## Part 12. Использование утилиты du

- Запустим `du`

![Part 12.1](images/part12-1.jpg)

- Выведем размеры /home, /var, /var/log - `sudo du -s -h /home && sudo du -s -h /var && sudo du -s -h /var/log`

![Part 12.2](images/part12-2.jpg)

- Выведем размер всех элементов /var/log - `sudo du -s -h /var/log/*`.

![Part 12.3](images/part12-3.jpg)

## Part 13. Установка и использование утилиты ncdu

- Установим ncdu - `sudo apt install ncdu`.

- Размеры /home и /var

![Part 13.1](images/part13-1.jpg)

- Размер /var/log

![Part 13.2](images/part13-2.jpg)

## Part 14. Работа с системными журналами

- Смотрим `cat /var/log/dmesg`

![Part 14.1](images/part14-1.jpg)

- Смотрим `cat /var/log/syslog`

![Part 14.2](images/part14-2.jpg)

- Смотрим `cat /var/log/auth.log`

![Part 14.3](images/part14-3.jpg)

- Для просмотра последней авторизации - `last`.

![Part 14.4](images/part14-4.jpg)

- Время авторизации - Jan 5 18:54
- имя пользователя - camillec
- метод входа в систему - tty1

- Перезапускаем службу SSHd - `service sshd restart`
- Выводим сообщение о рестарте службы - `sudo cat /var/log/syslog

![Part 14.5](images/part14-5.jpg)

## Part 15 использование планировщика заданий CRON

- Установим CRON - `sudo apt install cron`.
- Планируем задачу - `crontab -e`.
- В VIM прописываем - `*/2 * * * * uptime`.

![Part 15.1](images/part15-1.jpg)

- Выведем текущие задачи - `crontab -l`

![Part 15.2](images/part15-2.jpg)

- Выводим системный журнал - `sudo grep CRON /var/log/syslog`

![Part 15.3](images/part15-3.jpg)

- Удаляем задачи - `crontab -r`
- Смотрим задачи еще раз - 'crontab -l'

![Part 15.4](images/part15-4.jpg)