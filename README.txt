設備、環境
Linux sherloxk-raiderge77hx12ugs 6.1.26-1-MANJARO #1 SMP PREEMPT_DYNAMIC Wed Apr 26 22:07:35 UTC 2023 x86_64 GNU/Linux

使用程式語言:
C++ 17

UI 開元工具包 ：
Qt5

開發環境：
qt creator


檔案架構
.
├── 410977007_lupeichun_hw5_copy_file.pro

├── 410977007_lupeichun_hw5_copy_file.pro.user

├── callback.h

├── caller.h

├── copyFileCallback.h

├── main.cpp

├── mainwindow.cpp

└── mainwindow.h


檔案說明
1. ".pro", ".pro.user" 是跟使用者偏好設定、環境配置有關的檔案（配置執行qt的環境），與我編寫的程式碼無關。
2. main.cpp ：程式進入點
3. "mainwindow.cpp", "mainwindow.h" : ui 布局定義與實做
4. callback.h : 定義類別 Callback, 並定義純虛函數 updatePercentage，讓繼承的子類別必須實做。
5. copyFileCallback.h :
        定義類別 CopyFileCallback, 並繼承 Callback與實做 updatePercentage，這裡會更新進度條與在 console 輸出 percentage , 目前以完成的 bytes


操作影片：https://youtu.be/LwQlGxv5YJQ

google word :https://docs.google.com/document/d/1ZMLZ7nAT06eSsTfQQG-lyWoTuWRSlnlTJ3LH85R5IM0/edit?usp=sharing




