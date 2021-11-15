# Computational-Photography_HW3
# robot arm and rubber dock
## 姓名：賴柏霖
## 學號：609410151
## e-mail：609410151@alum.ccu.edu.tw
## 作業環境：Win10 64bit Visual studio 2019
## 編譯器：Visual Studio 2019
## 作業內容：
	1.建立一個3D場景：
		a.建立一個平面，將機械手臂和鴨子放在上面。
		b.調整固定視角，可以方便看到平面上放的物體。

	2.製作3D機械手臂，包含以下功能：
		a.機械手臂的構造包含：底座、上臂、前臂、夾子(手)，顏色不限盡量美觀即可。(若用貼圖，精美程度會另當bonus)
		b.利用鍵盤，可以控制機械手臂，包含：底座旋轉(base angle)、手臂關節角度(elbow angle)、手腕旋轉(wrist rotation)、夾子開關(claw open/close)。
		c.機械手臂的底座需要像夾娃娃機一樣，可以自由在平面上移動位置。
		![image](https://user-images.githubusercontent.com/72666141/141769509-bb8e87d2-0e28-43a0-bc56-25bd968e67f6.png)

	
	3.放置3D黃色小鴨：
		a.load小鴨模組，使用smf檔案

	4.場景光源設定，至少兩個光源(場景定點光源、可調控的聚光燈)：
		a.環境光：場景定點光源，固定對整個場景打光。
		b.可調控的聚光燈：初始位置，從機械手臂的正上方往下照。
		c.利用鍵盤，可以控制光源的顏色(紅、藍、綠)及方向(類似手電筒)。
		![image](https://user-images.githubusercontent.com/72666141/141769541-e969fcfa-bac3-426d-b284-f7c91b9f31db.png)

	5.按鍵功能的配置範例，(配置方法不限，可自行更動設定，但請在readme中將功能描述清楚)：
		-A、Z：旋轉機械手臂底座(順時針、逆時針)---底座旋轉(base angle)
		-S、X：調整機械手臂關節角度(伸直、彎曲)---手臂關節角度(elbow angle)
		-D、C：旋轉機械手腕(順時針、逆時針)-------手腕旋轉(wrist rotation)
		-F、V：開關夾子---------------------------夾子開關(claw open/close)
		-R：架子自動開關
		-Q：關閉程式
		-L：改變聚光燈顏色(預設白光，每按一次，依序變紅、藍、綠、白)
		-G、B、H、N：調整機械手臂的位置
		-J、M、I、K：調整聚光燈的方向(聚光點位置不變，照射的方向改變，類似手電筒)
		

