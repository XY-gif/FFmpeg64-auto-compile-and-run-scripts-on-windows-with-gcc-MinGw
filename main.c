#include <stdio.h>
#include <libavformat/avformat.h>
//用于打开视频文件
int main()
{
    const char* url = "./video.mp4";
    AVFormatContext *formatContext = avformat_alloc_context();
    if(!formatContext)
    {
        printf("avformat_alloc_context error\n");
        avformat_close_input(&formatContext);
        return -1;
    }


    // 当文件不带后缀名时可以强制指定文件格式
    //avformat_open_input(&formatContext,url,av_find_input_format("mp4"),NULL);
    if(avformat_open_input(&formatContext,url,NULL,NULL)<0)
    {
        printf("avformat_open_input error\n");
        if(!formatContext)
            avformat_close_input(&formatContext);//avformat_open_input要是失败了就会自动释放formatContext,所以此处防一手
        return -1;
    }

    if(avformat_find_stream_info(formatContext,NULL)<0)
    {
        printf("avformat_find_stream_info error\n");
        if(!formatContext)
            avformat_close_input(&formatContext);//avformat_open_input要是失败了就会自动释放formatContext,所以此处防一手
        return -1;
    }

// 用于根据参数，寻找流的索引号，参数除了第一个必须写，其它都是可选的，写的参数越多准确度越高。
// int av_find_best_stream(AVFormatContext *ic,     上下文指针
//                         enum AVMediaType type,   流的类型
//                         int wanted_stream_nb,    一般设置为-1，当为正或零的时候就会直接作为返回值返回
//                         int related_stream,      和我要找的流相关的流的索引，不用(写-1)也没事，就是准确度可能低一些
//                         const AVCodec **decoder_ret, 如果有就会直接返回解码器中的流
//                         int flags);              目前还没用这个参数，用作保留
    int video_index = av_find_best_stream(formatContext,AVMEDIA_TYPE_VIDEO,-1,-1,NULL,0);//在formatContext中找一个video
    int audio_index = av_find_best_stream(formatContext,AVMEDIA_TYPE_AUDIO,-1,video_index,NULL,0);

    printf("video_index:%d\n",video_index);
    printf("audio_index:%d\n",audio_index);
    printf("video_all_time:%llds\n",formatContext->duration/AV_TIME_BASE);

    // 要换成正常的时
    // printf("video_time:%lld\n",formatContext->streams[video_index]->duration);
    // printf("audio_time:%lld\n",formatContext->streams[audio_index]->duration);
    printf("video_time:%lf s\n", formatContext->streams[video_index]->duration * av_q2d(formatContext->streams[video_index]->time_base));
    printf("audio_time:%lf s\n", formatContext->streams[audio_index]->duration * av_q2d(formatContext->streams[audio_index]->time_base));

    printf("video_width:%d\n",formatContext->streams[video_index]->codecpar->width);
    printf("video_height:%d\n",formatContext->streams[video_index]->codecpar->height);


    //最好别猜，容易不对
    // AVRational  rate = av_guess_frame_rate(formatContext,formatContext->streams[video_index],NULL); 
    // printf("video_rate:%d/%d\n",rate.num/rate.den);
    AVRational rate;
    if (formatContext->streams[video_index]->avg_frame_rate.num == 0) //分子为0就选另外一个
        rate = formatContext->streams[video_index]->r_frame_rate;
    else 
        rate = formatContext->streams[video_index]->avg_frame_rate;
    printf("video_rate:%d/%d\n", rate.num,rate.den);
    // rate.num,rate.den分子和分母


    return 0;
}
