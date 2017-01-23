namespace Hulpdiensten_programma
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnOpenInsRap = new System.Windows.Forms.Button();
            this.btnSaveInsFile = new System.Windows.Forms.Button();
            this.btnOpenPolRap = new System.Windows.Forms.Button();
            this.btnSavePolRap = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnOpenInsRap
            // 
            this.btnOpenInsRap.Location = new System.Drawing.Point(13, 13);
            this.btnOpenInsRap.Margin = new System.Windows.Forms.Padding(4);
            this.btnOpenInsRap.Name = "btnOpenInsRap";
            this.btnOpenInsRap.Size = new System.Drawing.Size(188, 99);
            this.btnOpenInsRap.TabIndex = 0;
            this.btnOpenInsRap.Text = "Open insurance rapport";
            this.btnOpenInsRap.UseVisualStyleBackColor = true;
            this.btnOpenInsRap.Click += new System.EventHandler(this.btnOpenFile_Click);
            // 
            // btnSaveInsFile
            // 
            this.btnSaveInsFile.Location = new System.Drawing.Point(13, 120);
            this.btnSaveInsFile.Margin = new System.Windows.Forms.Padding(4);
            this.btnSaveInsFile.Name = "btnSaveInsFile";
            this.btnSaveInsFile.Size = new System.Drawing.Size(188, 100);
            this.btnSaveInsFile.TabIndex = 2;
            this.btnSaveInsFile.Text = "Save insurance Rapport";
            this.btnSaveInsFile.UseVisualStyleBackColor = true;
            this.btnSaveInsFile.Click += new System.EventHandler(this.btnSaveInsFile_Click);
            // 
            // btnOpenPolRap
            // 
            this.btnOpenPolRap.Location = new System.Drawing.Point(225, 13);
            this.btnOpenPolRap.Margin = new System.Windows.Forms.Padding(4);
            this.btnOpenPolRap.Name = "btnOpenPolRap";
            this.btnOpenPolRap.Size = new System.Drawing.Size(188, 97);
            this.btnOpenPolRap.TabIndex = 4;
            this.btnOpenPolRap.Text = "Open police rapport";
            this.btnOpenPolRap.UseVisualStyleBackColor = true;
            this.btnOpenPolRap.Click += new System.EventHandler(this.btnOpenPolRap_Click);
            // 
            // btnSavePolRap
            // 
            this.btnSavePolRap.Location = new System.Drawing.Point(225, 120);
            this.btnSavePolRap.Margin = new System.Windows.Forms.Padding(4);
            this.btnSavePolRap.Name = "btnSavePolRap";
            this.btnSavePolRap.Size = new System.Drawing.Size(188, 100);
            this.btnSavePolRap.TabIndex = 5;
            this.btnSavePolRap.Text = "Save police Rapport";
            this.btnSavePolRap.UseVisualStyleBackColor = true;
            this.btnSavePolRap.Click += new System.EventHandler(this.button2_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1304, 821);
            this.Controls.Add(this.btnSavePolRap);
            this.Controls.Add(this.btnOpenPolRap);
            this.Controls.Add(this.btnSaveInsFile);
            this.Controls.Add(this.btnOpenInsRap);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "Form1";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnOpenInsRap;
        private System.Windows.Forms.Button btnSaveInsFile;
        private System.Windows.Forms.Button btnOpenPolRap;
        private System.Windows.Forms.Button btnSavePolRap;
    }
}

