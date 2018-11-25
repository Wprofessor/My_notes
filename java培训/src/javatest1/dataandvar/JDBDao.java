package javatest1.dataandvar;

public class JDBDao {
    //利用接口通知save方法调用成功或失败信息
    public interface SaveListener{
        void onSucceed(String response);

        void onFail(Exception e);
    }
}
