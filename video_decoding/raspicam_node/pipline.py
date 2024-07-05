import sys
import os
import cv2
# import tools.demo as deploy
import copy
import time
# from cv2 import VideoWriter
import gi
# import share_memory_read as sm

from threading import Thread, Lock
from time import sleep
# import numpy as np

# from utils.plots import Annotator, colors
# from utils.general import (LOGGER, check_file, check_img_size, check_imshow, check_requirements, colorstr, cv2,
#                            increment_path, non_max_suppression, print_args, scale_coords, strip_optimizer, xyxy2xywh)

# sys.path.append(os.path.abspath(os.path.join(__file__, "..","..")))
# from Yolov5_StrongSORT_OSNet.track import track as yolov5_track

gi.require_version('Gst', '1.0')

from gi.repository import Gst, GObject, GLib
from numpy import size

file_name = 'output.mp4'
output_dir = './'
# predictor = deploy.build()


#pipe_time = PipeTimer()
warmup_frame = 50

"""
gst-launch-1.0  -v udpsrc port=5001 blocksize=512000 buffer-size=5120000 mtu=51200  
 ! 'application/x-rtp,media=video,clock-rate=90000,encoding-name=H264,payload=96' 
 ! rtph264depay ! 'video/x-h264,stream-format=byte-stream' 
 ! h264parse ! avdec_h264 ! videoconvert ! xvimagesink
~                                          
"""

def gstreamer_pipeline_v4l2(
    udp_port=5001,
    display_width=1280,
    display_height=800,
    framerate=15,
    flip_method=0,
):
    return (
        "udpsrc port=%d ! "
        "application/x-rtp,media=video,"
        "clock-rate=90000,encoding-name=H264,payload=96 ! "
        "rtph264depay ! "
        #"video/x-h264,stream-format=byte-stream ! "
        "h264parse ! "
        "nvv4l2decoder ! "
        "nvvidconv ! "
        "video/x-raw, width=%d, height=%d, format=BGRx ! "
        "videoconvert ! appsink"
        % (
            udp_port,
            display_width,
            display_height,
        )
    )


def gstreamer_pipeline(
    udp_port=5000,
    display_width=1280,
    display_height=800,
    framerate=21,
    flip_method=0,
):
    return (
        "udpsrc port=%d blocksize=512000 buffer-size=5120000 mtu=51200 ! "
        "application/x-rtp,media=video,clock-rate=90000,encoding-name=H264,payload=96 ! "
        "rtph264depay ! "
        "video/x-h264,stream-format=byte-stream ! "
        "h264parse ! "
        "avdec_h264 ! videoconvert ! xvimagesink "
        # "nvv4l2decoder ! "
        # "nvstreammux batch-size=1 width=1280 height=800 batched-push-timeout=40000 ! "
        # "nvvidconv ! "
        # "video/x-raw, width=%d, height=%d, format=BGRx ! "
        # "videoconvert ! appsink blocksize=51200 "
        % (
            udp_port,
            # display_width,
            # display_height,
        )
    )

def udp_push(image):

    pipeline = 'appsrc ! queue ! h264parse ! nvv4l2decoder ! nvvidconv \
        ! video/x-raw, width=640, height=480 ! nvv4l2h264enc ! rtph264depay \
            ! udpsink host=127.0.0.1 port=6000 sync=false'
    
    videoOut = VideoWriter()
    videoOut.open(pipeline, 0, 10, size(640,480), True)

    #write = cv2.VideoWriter(pipeline, cv2.CAP_GSTREAMER, 0, 30, 640*480, True)
    #write.write(image)

image_push_state = 0
def predict_video(video_file):

    # video_uri = gstreamer_pipeline(udp_port=5001)

    video_uri = gstreamer_pipeline_v4l2()

    print(video_uri)
    
    capture = cv2.VideoCapture(video_uri, cv2.CAP_GSTREAMER)

    #capture = cv2.VideoCapture(video_file)
    video_out_name = 'output.mp4' if file_name is None else file_name

    width = int(capture.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(capture.get(cv2.CAP_PROP_FRAME_HEIGHT))
    fps = int(capture.get(cv2.CAP_PROP_FPS))
    frame_count = int(capture.get(cv2.CAP_PROP_FRAME_COUNT))

    print("video fps:%d, frame_count:%d, video_width:%d, video_height:%d" 
           % (fps, frame_count, width, height))

    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    out_path = os.path.join(output_dir, video_out_name)

    fourcc = cv2.VideoWriter_fourcc(* 'mp4v') #
    writer = cv2.VideoWriter(out_path, fourcc, 30, (width, height))
    #writer = cv2.VideoWriter(out_path, fps, (width, height))

    global frame_id
    frame_id = 0

    total_time = 0

    global udp_pipline
    #udp_pipline = RtpPipeline()

    framecount = 0

    ######################recevie from kcf_ptz##############
    #video_uri_kcf = gstreamer_pipeline_v4l2()

    #capture_kcf = cv2.VideoCapture(video_uri_kcf, cv2.CAP_GSTREAMER)
    ########################################################

    # cmd = sm.receive_cmd()
    # print("starting ------------------->>>>>{},cmd----->>>>{}".format(video_source, cmd))

    lock_push.acquire()
    lock_push_end.acquire()
    # push_thread = Thread(target=push_image_thread, name='push_image', args=(3,))
    # push_thread.start()

    global image_push
    global image_push_state
    global infer_out
    image_push_state = 0

    while(1):
        #old_time = time.time()

        ##########kcf video######
        #video_source = sm.get_video_source()
        # if(video_source == '1'):
        #     ret, frame = capture_kcf.read()
        #     udp_pipline.pip_push(frame)
        #     continue

        #if frame_id % 10 == 0:
        #    print('frame id: ', frame_id)
        ret, frame = capture.read()

        # udp_pipline.pip_push(frame)
        # continue

        if not ret:
            print('capture failed , id: ', frame_id)
            break

        # if(video_source == '1'):
        #     udp_pipline.pip_push(frame)
        #     frame_id += 1
        #     continue

        framecount += 1


        if(framecount == 2):
            framecount = 0
            #continue

        #print("frame count:{}", framecount)

        old_time = time.time()

        #print("cmd is ------------------->>>>>{}".format(cmd))

        cv2.imshow("TTA_DET", frame)

        frame_id += 1

        current_time = time.time()
        fps_time = current_time - old_time
        total_time += fps_time
        print("fps time: " + str(fps_time))

        keyCode = cv2.waitKey(10) & 0xFF
        # Stop the program on the ESC key
        if keyCode == 27:
            break

        time.sleep(0.01)

    print("total time is {}".format(total_time))



class RtpPipeline(object):
    def __init__(self):
        self.number_frames = 0
        self.fps = 30
        #self.cap = cv2.VideoCapture(0)             '! queue ! videoconvert ' \
        self.duration = 1 / self.fps * Gst.SECOND  # duration of a frame in nanoseconds
#! video/x-raw,width=640,height=480 
        self.launch_string = 'appsrc name=source is-live=true blocksize=51200 max-bytes=2000000 ' \
            'caps=video/x-raw,format=BGR,width=1280,height=800 ' \
            '! videoconvert ' \
            '! queue ' \
            '! nvvidconv ! video/x-raw(memory:NVMM),width=1080,height=720,format=NV12' \
            '! nvv4l2h264enc preset-level=2 iframeinterval=10 control-rate=1 bitrate=3000000 ' \
            'profile=0 insert-sps-pps=true ! video/x-h264, stream-format=byte-stream ! rtph264pay name=pay0 pt=96 ' \
            '! queue ' \
            '! udpsink host=192.168.10.255 port=6000 sync=false blocksize=51200 buffer-size=512000'

        #'! nvvidconv ! video/x-raw(memory:NVMM),width=1280,height=800,format=NV12,framerate=1/30' \
        #'! nvv4l2h264enc ! video/x-h264,preset-level=0,control-rate=2,bitrate=1000000,' \
        #    'profile=baseline,stream-format=byte-stream ! h264parse ! rtph264pay name=pay0 pt=96 ' \

        #'! nvv4l2h264enc ! rtph264pay name=pay0 pt=96 ' \

        #    '! nvv4l2h264enc profile=4 iframeinterval=30 bitrate=2000000 ! rtph264pay name=pay0 pt=96 ' \
        # self.launch_string = 'appsrc name=source is-live=true ' \
        #     'caps=video/x-raw,format=BGR,width=640,height=480 ' \
        #     '! videoconvert ! video/x-raw,width=640,height=480 ' \
        #     '! x264enc speed-preset=ultrafast tune=zerolatency ! rtph264pay name=pay0 pt=96 ' \
        #     '! udpsink host=192.168.10.255 port=5500 sync=false'
        Gst.init(None)

        Gst.debug_set_default_threshold(2)

        pipeline = Gst.parse_launch(self.launch_string)
        self.appsrc = pipeline.get_child_by_name('source')
        pipeline.set_state(Gst.State.PLAYING)

    def pip_push(self, frame):
        try:
            #ret, frame = self.cap.read()
            start = time.time()
            data = frame.tobytes()
            length = len(data)
            buf = Gst.Buffer.new_allocate(None, length, None)
            buf.fill(0, data)
            buf.duration = self.duration
            timestamp = self.number_frames * self.duration
            buf.pts = buf.dts = int(timestamp)
            buf.offset = timestamp
            self.number_frames += 1
            retval = self.appsrc.emit('push-buffer', buf)
            if retval != Gst.FlowReturn.OK:
                print(retval)
        except Exception as e:
            print("error message----->>{}".format(e))
            return

lock_push = Lock()
lock_push_end = Lock()
infer_out=[]
def push_image_thread(n):
    global image_push
    global udp_pipline
    global frame_id
    global image_push_state
    global infer_out

    while(True):
        push_count = 0
        #if lock_push.acquire():

        if image_push_state == 1:
            
            outputs, result_image = deploy.predict(predictor, image_push, frame_id)
            print("push image thread image ---------------------{}".format(outputs))
            # if len(outputs) != 0:
            #     print("push infer image!!!!!!!!!!!!!!")
                #udp_pipline.pip_push(result_image)

            infer_out = outputs
            image_push_state = 0

            outputs, result_image=yolov5_track(image_push, outputs)
            
        time.sleep(0.01)

            #lock_push_end.release()
        #print("push count------------------------------------------------->>>{}".format(push_count))


if __name__ == "__main__":

    predict_video("vtl_output.mp4")


