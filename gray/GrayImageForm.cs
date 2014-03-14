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
    }
}
