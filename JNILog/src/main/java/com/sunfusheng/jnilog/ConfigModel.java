package com.sunfusheng.jnilog;

/**
 * @author by sunfusheng on 2018/11/29
 */
public class ConfigModel {
    public int x; // 4字节
    public float y; // 4字节
    public double z; // 8字节

    public byte[] toBytes() {
        byte[] bytes = new byte[16];
        int pos = 0;
        System.arraycopy(SerializeUtil.intToBytes(x), 0, bytes, pos, 4);
        pos += 4;
        System.arraycopy(SerializeUtil.floatToBytes(y), 0, bytes, pos, 4);
        pos += 4;
        System.arraycopy(SerializeUtil.doubleToBytes(z), 0, bytes, pos, 8);
        return bytes;
    }

    public void fromBytes(byte[] bytes) {
        int pos = 0;
        byte[] result = new byte[8];
        System.arraycopy(bytes, pos, result, 0, 4);
        pos += 4;
        this.x = SerializeUtil.bytesToInt(result);

        System.arraycopy(bytes, pos, result, 0, 4);
        pos += 4;
        this.y = SerializeUtil.bytesToFloat(result);

        System.arraycopy(bytes, pos, result, 0, 8);
        this.z = SerializeUtil.bytesToDouble(result);
    }

    @Override
    public String toString() {
        return "x=" + x +
                ", y=" + y +
                ", z=" + z;
    }
}
