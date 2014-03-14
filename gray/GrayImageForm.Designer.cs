namespace gray {
    partial class GrayImage {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent() {
            this.Open = new System.Windows.Forms.Button();
            this.SaveBtn = new System.Windows.Forms.Button();
            this.CloseBtn = new System.Windows.Forms.Button();
            this.PixBtn = new System.Windows.Forms.Button();
            this.MemBtn = new System.Windows.Forms.Button();
            this.PointerBtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // Open
            // 
            this.Open.Location = new System.Drawing.Point(37, 32);
            this.Open.Name = "Open";
            this.Open.Size = new System.Drawing.Size(75, 23);
            this.Open.TabIndex = 0;
            this.Open.Text = "打开文件";
            this.Open.UseVisualStyleBackColor = true;
            this.Open.Click += new System.EventHandler(this.OpenBtn_Click);
            // 
            // SaveBtn
            // 
            this.SaveBtn.Location = new System.Drawing.Point(37, 61);
            this.SaveBtn.Name = "SaveBtn";
            this.SaveBtn.Size = new System.Drawing.Size(75, 23);
            this.SaveBtn.TabIndex = 1;
            this.SaveBtn.Text = "保存图像";
            this.SaveBtn.UseVisualStyleBackColor = true;
            this.SaveBtn.Click += new System.EventHandler(this.SaveBtn_Click);
            // 
            // CloseBtn
            // 
            this.CloseBtn.Location = new System.Drawing.Point(37, 90);
            this.CloseBtn.Name = "CloseBtn";
            this.CloseBtn.Size = new System.Drawing.Size(75, 23);
            this.CloseBtn.TabIndex = 2;
            this.CloseBtn.Text = "关闭";
            this.CloseBtn.UseVisualStyleBackColor = true;
            this.CloseBtn.Click += new System.EventHandler(this.CloseBtn_Click);
            // 
            // PixBtn
            // 
            this.PixBtn.Location = new System.Drawing.Point(37, 157);
            this.PixBtn.Name = "PixBtn";
            this.PixBtn.Size = new System.Drawing.Size(75, 23);
            this.PixBtn.TabIndex = 3;
            this.PixBtn.Text = "提取像素法";
            this.PixBtn.UseVisualStyleBackColor = true;
            this.PixBtn.Click += new System.EventHandler(this.PixBtn_Click);
            // 
            // MemBtn
            // 
            this.MemBtn.Location = new System.Drawing.Point(37, 186);
            this.MemBtn.Name = "MemBtn";
            this.MemBtn.Size = new System.Drawing.Size(75, 23);
            this.MemBtn.TabIndex = 4;
            this.MemBtn.Text = "内存法";
            this.MemBtn.UseVisualStyleBackColor = true;
            this.MemBtn.Click += new System.EventHandler(this.MemBtn_Click);
            // 
            // PointerBtn
            // 
            this.PointerBtn.Location = new System.Drawing.Point(37, 215);
            this.PointerBtn.Name = "PointerBtn";
            this.PointerBtn.Size = new System.Drawing.Size(75, 23);
            this.PointerBtn.TabIndex = 5;
            this.PointerBtn.Text = "指针法";
            this.PointerBtn.UseVisualStyleBackColor = true;
            this.PointerBtn.Click += new System.EventHandler(this.PointerBtn_Click);
            // 
            // GrayImage
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(585, 369);
            this.Controls.Add(this.PointerBtn);
            this.Controls.Add(this.MemBtn);
            this.Controls.Add(this.PixBtn);
            this.Controls.Add(this.CloseBtn);
            this.Controls.Add(this.SaveBtn);
            this.Controls.Add(this.Open);
            this.Name = "GrayImage";
            this.Text = "GrayImage";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button Open;
        private System.Windows.Forms.Button SaveBtn;
        private System.Windows.Forms.Button CloseBtn;
        private System.Windows.Forms.Button PixBtn;
        private System.Windows.Forms.Button MemBtn;
        private System.Windows.Forms.Button PointerBtn;
    }
}

