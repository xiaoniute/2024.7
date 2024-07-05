1、机载盒子支持ffmpeg 版本v2.8； 车载盒子 ffmpeg402.7
2、lib为解码所需库
3、DjiRtspImageSource service(rtsp_url);
      此函数加载rtsp推流地址
4、service.setImageCallback(nullptr, [&ts](void* handler, uint8_t* frmdata, int frmsize, int width, int height, int pixfmt)
     此回调函数中，frmdate为图片数据，可直接在opencv中使用。
     或如demo中，先保存为jpg图片。

5、service.start();  //开始解析

6、service.stop();   //停止解析


注：车载盒子和机载盒子区别为ffmpeg库的版本，根据需要选择使用
	