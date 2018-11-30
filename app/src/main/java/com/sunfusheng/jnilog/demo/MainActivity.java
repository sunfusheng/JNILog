package com.sunfusheng.jnilog.demo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.sunfusheng.jnilog.ConfigModel;
import com.sunfusheng.jnilog.JNILogWrapper;
import com.sunfusheng.jnilog.LogUtil;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = findViewById(R.id.tv);

        StringBuilder sb = new StringBuilder();
        sb.append(JNILogWrapper.stringFromJNI());
        sb.append("\n\n");

        ConfigModel inputConfig = new ConfigModel();
        inputConfig.x = 1;
        inputConfig.y = 2.2f;
        inputConfig.z = 3.33;

        sb.append("输入配置：");
        sb.append(inputConfig.toString());
        sb.append("\n");

        double factor = 2;

        sb.append("乘数因子：");
        sb.append(factor);
        sb.append("\n");

        ConfigModel outputConfig = JNILogWrapper.convertConfigModelWrapper(inputConfig, factor);

        sb.append("输出配置：");
        sb.append(outputConfig.toString());
        sb.append("\n");

        tv.setText(sb);
    }

}
