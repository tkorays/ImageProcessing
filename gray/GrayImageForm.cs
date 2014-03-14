using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace gray {
    public partial class GrayImage : Form {
        private string curFileName;
        private System.Drawing.Bitmap curBitmap;
        public GrayImage() {
            InitializeComponent();
        }

        private void OpenBtn_Click(object sender, EventArgs e) {
            OpenFileDialog opnDlg = new OpenFileDialog();
            opnDlg.Filter = "所有图像文件|*.bmp;*.pcx;*.jpg;*.jpeg;*.gif;";
            opnDlg.Title = "打开图像文件";
            opnDlg.ShowHelp = true;
            if (opnDlg.ShowDialog()==DialogResult.OK) {
                curFileName = opnDlg.FileName;
                try {
                    curBitmap = (Bitmap)Image.FromFile(curFileName);
                } catch (Exception exp) {
                    MessageBox.Show(exp.Message);
                }
            }
            Invalidate();
        }

        private void SaveBtn_Click(object sender, EventArgs e) {
            if (curBitmap==null) {
                return;
            }
            SaveFileDialog saveDlg = new SaveFileDialog();
            saveDlg.Title = "保存为";
            saveDlg.OverwritePrompt = true; // 改写已存在文件时提醒用户
            saveDlg.Filter = "BMP文件 (*.bmp) | *.bmp|" + "Gif文件 (*.gif) | *.gif|"+"JPEG文件 (*.jpg) | *.jpg|"+"PNG文件 (*.png) | *.png";
            saveDlg.ShowHelp = true;
            if (saveDlg.ShowDialog()==DialogResult.OK) {
                string fileName = saveDlg.FileName;
                string strFiExtn = fileName.Remove(0, fileName.Length - 3);

                switch (strFiExtn) {
                    case "bmp":
                        curBitmap.Save(fileName, System.Drawing.Imaging.ImageFormat.Bmp);
                        break;
                    case "jpg":
                        curBitmap.Save(fileName, System.Drawing.Imaging.ImageFormat.Jpeg);
                        break;
                    case "png":
                        curBitmap.Save(fileName, System.Drawing.Imaging.ImageFormat.Png);
                        break;
                    default:
                        break;
                }
            }
        }

        private void CloseBtn_Click(object sender, EventArgs e) {
            this.Close();
        }

        protected override void OnPaint(PaintEventArgs e) {
            base.OnPaint(e);
            Graphics g = e.Graphics;
            if (curBitmap!=null) {
                g.DrawImage(curBitmap, 160, 20, 300, 200);
            }
        }
        // 好慢啊
        private void PixBtn_Click(object sender, EventArgs e) {
            if (curBitmap != null) {
                Color curColor;
                int ret;
                for (int i = 0; i < curBitmap.Width; i++) {
                    for (int j = 0; j < curBitmap.Height; j++) {
                        curColor = curBitmap.GetPixel(i, j);
                        ret = (int)(curColor.R * 0.299 + curColor.G * 0.587 + curColor.B * 0.114);
                        curBitmap.SetPixel(i, j, Color.FromArgb(ret, ret, ret));
                    }
                }
                Invalidate();
            }
        }
        // 这个效率不错！！！
        // 把数据复制到内存中，这样可以是程序的运行速度大大提高。
        private void MemBtn_Click(object sender, EventArgs e) {
            if (curBitmap!=null) {
                Rectangle rect = new Rectangle(0, 0, curBitmap.Width, curBitmap.Height);
                System.Drawing.Imaging.BitmapData bmpDate = curBitmap.LockBits(rect, System.Drawing.Imaging.ImageLockMode.ReadWrite, curBitmap.PixelFormat);
                IntPtr ptr = bmpDate.Scan0; // 得到首地址

                int bytes = curBitmap.Width * curBitmap.Height * 3; // r g b
                byte[] rgbValues = new byte[bytes];
                // 复制被锁定的图像到该数组
                System.Runtime.InteropServices.Marshal.Copy(ptr, rgbValues, 0, bytes);
                double colorTemp = 0;
                for (int i = 0; i < rgbValues.Length; i+=3) {
                    colorTemp = rgbValues[i + 2] * 0.299 + rgbValues[i + 1] * 0.587 + rgbValues[i] * 0.114;
                    rgbValues[i + 2] = rgbValues[i + 1] = rgbValues[i] = (byte)colorTemp;
                }
                System.Runtime.InteropServices.Marshal.Copy(rgbValues, 0, ptr, bytes);
                curBitmap.UnlockBits(bmpDate);
                Invalidate();
            }
        }

        private void PointerBtn_Click(object sender, EventArgs e) {
            MessageBox.Show("槽！！不安全的代码！算了~~在C#里面就不折腾指针了!");

        }

        
    }
}
