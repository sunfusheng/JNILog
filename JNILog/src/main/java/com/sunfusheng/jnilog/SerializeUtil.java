package com.sunfusheng.jnilog;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.Serializable;

/**
 * @author by sunfusheng on 2018/11/29
 */
public class SerializeUtil {

    public static byte[] intToBytes(int i) {
        byte[] data = new byte[4];
        data[0] = (byte) i;
        data[1] = (byte) (i >> 8);
        data[2] = (byte) (i >> 16);
        data[3] = (byte) (i >> 24);
        return data;
    }

    public static int bytesToInt(byte[] data) {
        return (0xff & data[0]) | (0xff00 & (data[1] << 8)) | (0xff0000 & (data[2] << 16))
                | (0xff000000 & (data[3] << 24));
    }

    public static boolean bytesToBoolean(byte[] data) {
        return data[0] > 0;
    }

    public static byte[] longToBytes(long l) {
        byte[] data = new byte[8];
        data[0] = (byte) l;
        data[1] = (byte) (l >> 8);
        data[2] = (byte) (l >> 16);
        data[3] = (byte) (l >> 24);
        data[4] = (byte) (l >> 32);
        data[5] = (byte) (l >> 40);
        data[6] = (byte) (l >> 48);
        data[7] = (byte) (l >> 56);
        return data;
    }

    public static long bytesToLong(byte[] data) {
        return (long) (0xff & data[0]) | ((long) (0xff & data[1]) << 8)
                | ((long) (0xff & data[2]) << 16) | ((long) (0xff & data[3]) << 24)
                | ((long) (0xff & data[4]) << 32) | ((long) (0xff & data[5]) << 40)
                | ((long) (0xff & data[6]) << 48) | ((long) (0xff & data[7]) << 56);
    }

    public static byte[] floatToBytes(float f) {
        return intToBytes(Float.floatToIntBits(f));
    }


    public static float bytesToFloat(byte[] data) {
        return Float.intBitsToFloat(bytesToInt(data));
    }


    public static byte[] doubleToBytes(double d) {
        return longToBytes(Double.doubleToLongBits(d));
    }


    public static double bytesToDouble(byte[] data) {
        return Double.longBitsToDouble(bytesToLong(data));
    }

}
