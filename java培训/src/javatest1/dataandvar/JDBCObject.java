package javatest1.dataandvar;

import java.io.IOException;

public class JDBCObject {
    public void save(JDBDao.SaveListener listener) {
        okhttp3.Response response = JDBCHelper.getInstance().save(this);//保存对象，获取Response响应
        //响应不为空 并且响应码为201 (201在HTTP协议中表示请求成功并且服务器创建了新的资源)
        if (null != response && response.code() == 201) {
            if (response.code() == 201) {
                try {
                    //获取响应的内容
                    String json = response.body().string();
                    listener.onSucceed(json);
                } catch (IOException e) {
                    e.printStackTrace();
                    listener.onFail(e);
                }
            }
        } else {
        //存储失败
            Exception e = new Exception("save failed!");
            listener.onFail(e);
        }
    }
}
