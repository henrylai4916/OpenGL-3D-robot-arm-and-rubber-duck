# OpenGL 3D robot arm and rubber dock 
## 計算攝影學：應用圖學與影像技術_HW3
## Demo影片：
[![IMAGE ALT TEXT](https://user-images.githubusercontent.com/72666141/164231452-f68fbaad-1c60-46e0-9fff-cf64c104d83c.JPG)](https://www.youtube.com/watch?v=GRcNxCQtLs0)

## 實現功能：
### 1. 建立一個3D場景：
	a. 建立一個平面，將機械手臂和鴨子放在上面。
	b. 調整固定視角，可以方便看到平面上放的物體。
https://user-images.githubusercontent.com/72666141/146047093-ca42a9c2-fd4d-42d5-a0ff-448fd7ab33ac.mp4

---

### 2. 製作3D機械手臂，包含以下功能：
	a. 機械手臂的構造包含：底座、上臂、前臂、夾子(手)
	b. 利用鍵盤，可以控制機械手臂，包含：底座旋轉(base angle)、手臂關節角度(elbow angle)、手腕旋轉(wrist rotation)、夾子開關(claw open/close)。
	c. 機械手臂的底座需要像夾娃娃機一樣，可以自由在平面上移動位置。
	d. 按鍵功能：
		-A、Z：旋轉機械手臂底座(順時針、逆時針)---底座旋轉(base angle)
		-S、X：調整機械手臂關節角度(伸直、彎曲)---手臂關節角度(elbow angle)
		-D、C：旋轉機械手腕(順時針、逆時針)-------手腕旋轉(wrist rotation)
		-F、V：開關夾子---------------------------夾子開關(claw open/close)
		-R：架子自動開關
		-Q：關閉程式
![image](https://user-images.githubusercontent.com/72666141/141769732-add5e6f8-f363-40b4-878e-267363b78e9f.png)


https://user-images.githubusercontent.com/72666141/146048024-890678f4-c46a-4bf3-aaef-0a5f00e24535.mp4

---
	
### 3. 放置3D黃色小鴨：
	a. load小鴨模組，使用smf檔案

---

### 4. 場景光源設定，至少兩個光源(場景定點光源、可調控的聚光燈)：
	a.環境光：場景定點光源，固定對整個場景打光。
	b.可調控的聚光燈：初始位置，從機械手臂的正上方往下照。
	c.利用鍵盤，可以控制光源的顏色(紅、藍、綠)及方向(類似手電筒)。
	d. 按鍵功能：
		-L：改變聚光燈顏色(預設白光，每按一次，依序變紅、藍、綠、白)
		-G、B、H、N：調整機械手臂的位置
		-J、M、I、K：調整聚光燈的方向(聚光點位置不變，照射的方向改變，類似手電筒)
![image](https://user-images.githubusercontent.com/72666141/141769541-e969fcfa-bac3-426d-b284-f7c91b9f31db.png)

https://user-images.githubusercontent.com/72666141/146048558-74e92b1b-5857-4c3c-90b8-0df76f986f7c.mp4
