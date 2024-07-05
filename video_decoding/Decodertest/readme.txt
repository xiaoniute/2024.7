1、支持ffmpeg 版本v2.8
2、lib为解码所需库
3、DjiRtspImageSource service(rtsp_url);
      此函数加载rtsp推流地址
4、service.setImageCallback(nullptr, [&ts](void* handler, uint8_t* frmdata, int frmsize, int width, int height, int pixfmt)
     此回调函数中，frmdate为图片数据，可直接在opencv中使用。
     或如demo中，先保存为jpg图片。

5、service.start();  //开始解析

6、service.stop();   //停止解析
	