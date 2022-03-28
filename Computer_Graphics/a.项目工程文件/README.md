

## Multi-person Human Pose Estimation and Tracking in Soccer Videos Based on LightTrack

### Finished on 1/4/2022: 
**The code is derived from:**

https://github.com/Guanghan/lighttrack

**What the code can do:**

Input a video with humans 

->
Output the video with people's skeleton key points marked

**How to get ready:**
- Unzip the code.zip
  ```Shell
  cd lighttrack
  ```
- Prepare the environment
  ```Shell
  conda env create -f environment.yml
  ```
- Compile
  ```Shell
  cd lib
  make

  cd ../graph/torchlight
  python setup.py install
  ```

- Download weights
  ```Shell
   cd ../../weights;
   bash ./download_weights.sh
   ```
- Prepare the input video
  ```Shell
   cd ../data/demo;
   # put the video you wanna precess here
   ```
- Run
  ```Shell
   cd ../../;
   python demo_video_mobile.py
   ```
- Check the output
  ```Shell
   cd data/demo/videos
   # check the output video
   cd ../jsons
   # check the output .json files
   ```